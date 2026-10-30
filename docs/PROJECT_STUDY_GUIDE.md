# Push_swap: project study guide

This guide explains how the current project is organized and how data flows
through its two programs: `push_swap`, which generates a sorting program, and
`checker`, which executes and validates such a program.

The project is written in C. Its central constraint is that the stacks can
only be changed by the allowed Push_swap operations. The goal is therefore
not just to sort the integers, but to find a short valid operation sequence.

## 1. Big picture

The main program follows this pipeline:

1. Parse command-line flags and integers.
2. Store the integers in stack A as a linked list; initialize stack B empty.
3. Sort pointers to the stack nodes, assign each node a rank, and count input
   inversions.
4. If the stack is already sorted, emit no operations. Otherwise choose a
   strategy and execute it using the stack-operation functions.
5. Free both stacks.

The checker follows a related but distinct pipeline:

1. Parse and rank the initial integers.
2. Read operation lines from standard input.
3. Execute each recognized operation without echoing it.
4. Print `OK` if A is sorted by its original values and B is empty; otherwise
   print `KO`.

The high-level entry points are `d_main.c` for `push_swap` and
`b_checker_bonus.c` for `checker`.

## 2. Data model

### Stack nodes

`o_operations.h` defines a stack node:

```c
typedef struct s_stack
{
    int             number;
    int             index;
    struct s_stack  *next;
}   t_stack;
```

Each node keeps:

- `number`: the original input integer. The checker uses this value to verify
  the final ascending order.
- `index`: the node's rank in the sorted input. Sorting strategies compare
  ranks instead of raw integers.
- `next`: a pointer to the next node. The top of a stack is the pointer held
  by `stack_a` or `stack_b`.

A stack is therefore represented by a singly linked list. Operations that
change its top receive a pointer to that top pointer (`t_stack **`) so they
can update the caller's stack.

### Configuration and algorithm state

`d_push_swap.h` defines shared types:

- `t_run_config`: selected mode and whether benchmark reporting is enabled.
- `t_parse_context`: parser state, including list tail and number/flag counts.
- `t_strategy_info`: the selected strategy's display name and complexity
  description.
- `t_request`: the input passed to the strategy selector.
- `t_operation` and `t_bench_state`: operation identifiers and benchmark
  counters.

The insertion implementation has its own `t_insertion_move` in
`a_insertion.h`. It records the signed rotations needed in A and B, their
estimated combined cost, and whether a candidate has been selected.

## 3. Command-line parsing

`d_parser.c` implements `parse_args` and its private helpers.

### Flags and defaults

The default strategy is `--adaptive`. The recognized modes are:

- `--simple`
- `--medium`
- `--complex`
- `--adaptive`

`--bench` enables benchmark reporting. Flags are accepted only before the
first number. Once number parsing starts, a later argument beginning with
`--` is an error. Repeating a mode or repeating `--bench` is also rejected.

Both separate integer arguments and a quoted, space-separated argument are
supported:

```sh
./push_swap --medium 8 -3 0 42
./push_swap "--medium" "8 -3 0 42"
```

### Integer parsing and stack construction

`parse_str` walks each number string, skips spaces, and calls `parse_int`.
`parse_int` accepts an optional sign and decimal digits. It checks the
accumulator against the appropriate positive or negative `int` limit before
each multiply-and-add, so a long digit string is rejected before the
accumulator can overflow.

Each parsed value is appended to the tail of stack A. Appending preserves
input order. Empty input and invalid input lead to `error_exit`, which frees
the current stack, writes `Error` to standard error, and exits unsuccessfully.

Duplicate detection happens later, during index assignment. This separation
lets the parser focus on syntax and integer range while the ranking pass
validates uniqueness.

## 4. Ranking and disorder measurement

`d_index.c` implements `index_stack`. It allocates two arrays of node pointers:

- `arr`, which points to the nodes in the linked list;
- `tmp`, the temporary array used by merge sort.

The nodes themselves remain in their original linked-list order during this
step; sorting the pointer array is enough to discover their relative ranks.

### Merge sort and inversion counting

The merge sort divides the pointer array into halves, recursively sorts each
half by `number`, and merges the halves into `tmp`.

If a value from the right half is smaller than the next value from the left
half, it forms an inversion with every unmerged value remaining in the left
half. The merge step adds `mid - i + 1` to the inversion count. This counts
all out-of-order pairs in `O(n log n)` time rather than checking all pairs in
`O(n²)` time.

### Assigning ranks

After sorting, `assign_index` walks the pointer array in ascending numeric
order:

- smallest number gets index `0`;
- next number gets index `1`;
- largest number gets index `n - 1`.

If two neighboring sorted values are equal, the input contains a duplicate
and is rejected. Otherwise these ranks form a compact permutation from
`0` through `n - 1`. They make algorithm behavior independent of whether the
original values are negative, very large, or far apart.

### Disorder ratio

`d_main.c` normalizes the inversion count:

```text
maximum inversions = n * (n - 1) / 2
disorder = inversions / maximum inversions
```

The ratio is `0` for already sorted input and `1` for reverse-sorted input.
For zero or one element, the maximum is zero and the helper returns zero.
This measure is used by the adaptive strategy; it is a heuristic about input
order, not a direct prediction of the number of operations a strategy will
emit.

## 5. The operation set

The public operation declarations are in `o_operations.h`; implementations
are in `o_push.c`, `o_swap.c`, `o_rotate.c`, and `o_rev_rotate.c`.

| Operation | Stack effect |
|---|---|
| `sa` | Swap the top two elements of A. |
| `sb` | Swap the top two elements of B. |
| `ss` | Swap the top two elements of both stacks. |
| `pa` | Push the top of B onto A. |
| `pb` | Push the top of A onto B. |
| `ra` | Move A's top element to its bottom. |
| `rb` | Move B's top element to its bottom. |
| `rr` | Rotate A and B together. |
| `rra` | Move A's bottom element to its top. |
| `rrb` | Move B's bottom element to its top. |
| `rrr` | Reverse rotate A and B together. |

Swap and rotation operations on a stack with fewer than two nodes do not
change that stack. A push from an empty source stack does nothing.

Each public operation performs three related tasks:

1. Apply the pointer changes to one or both linked lists.
2. Record its operation identifier for the benchmark, if benchmarking is
   enabled.
3. Print its instruction through `write_operation`.

`m_benchmark_state.c` owns the output switch. `push_swap` leaves operation
printing enabled; `checker` disables it before executing input instructions.
That allows both programs to share exactly the same stack operations without
the checker echoing its input.

## 6. Sorting strategies

`a_strategy.c` selects the requested strategy. `a_sort.c` contains dedicated
small-input routines; the other algorithms are in `a_insertion*.c`,
`a_chunk.c`, and `a_radix.c`.

### Small inputs: two to five elements

Adaptive mode uses specialized routines for sizes 2 through 5:

- `two_sort` swaps the two values.
- `three_sort` handles the six possible permutations of three distinct
  ranks with a small fixed combination of swaps and rotations.
- `four_sort` brings rank `0` to A's top, pushes it to B, sorts the remaining
  three ranks, then pushes rank `0` back.
- `five_sort` pushes ranks `0` and `1` to B, sorts the remaining three, and
  restores the two smallest ranks.

The helper that brings a requested rank to A's top chooses between forward
and reverse rotation based on which direction takes fewer steps.

### Simple: greedy insertion

The insertion strategy maintains B in circular descending order while
transferring values from A:

1. Push the top of A to B to seed the circular order.
2. For every remaining node in A, find the place in B where its rank belongs.
   The insertion point is the position immediately after the larger
   neighboring rank, including the wraparound boundary between the maximum
   and minimum.
3. Estimate the cost for every candidate in A. A signed positive rotation
   means forward (`ra`/`rb`); a signed negative rotation means reverse
   (`rra`/`rrb`).
4. Consider both directions for each stack. If both rotations have the same
   sign, the first steps can be combined with `rr` or `rrr`; their combined
   cost is the larger rotation magnitude. If the signs differ, their costs
   add.
5. Select the candidate with the smallest estimated number of rotations.
   Apply all shared rotations, then the remaining rotations on each stack,
   and push the selected value from A to B.
6. Once A is empty, rotate the largest rank in B to its top and repeatedly
   push B back to A. This yields ascending order in A.

This is a greedy decision: it minimizes the estimated immediate cost at each
transfer, not the total cost over every possible future sequence. Candidate
evaluation repeatedly scans the stacks, so reducing emitted operations comes
at the cost of more computation than simply inserting A's current top.

The implementation is split across three files to comply with the project's
limits on functions per source file and lines per function:

- `a_insertion.c`: overall loop and final restoration;
- `a_insertion_cost.c`: insertion positions and candidate cost comparisons;
- `a_insertion_moves.c`: execution of combined and individual rotations.

### Medium: chunks

`a_chunk.c` transfers ranks from A to B using a moving rank window. Its width
is approximately `sqrt(n)` (with a minimum of 2).

- If A's top rank is at or below the next expected rank, it is pushed to B
  and B is rotated, placing the smaller rank deeper.
- If the rank is within the current window, it is pushed to B without that
  extra rotation.
- If it is above the window, A is rotated and scanned again.

After transferring every value, the algorithm searches for the largest
remaining rank in B, rotates it to the top using the shorter direction, and
pushes it to A. Repeating this in descending rank order builds ascending
order in A. Chunking is a heuristic: the number of operations depends on the
input permutation and chosen window width.

### Complex: binary radix

`a_radix.c` applies least-significant-bit-first radix sort to the compact
non-negative ranks:

1. Determine the number of bits needed to represent `n - 1`.
2. For each bit position, inspect exactly the current number of nodes in A.
3. If the current rank has a `1` in that bit, rotate it to the bottom of A.
   If it has a `0`, push it to B.
4. Push every node from B back to A before processing the next bit.

After processing each successive bit, the ranks are ordered by all bits seen
so far. Once the highest needed bit has been processed, A is sorted. There
are `O(log n)` passes, each inspecting `n` nodes, so this method has
predictable `O(n log n)` time and operation growth, though its operation
count is not always as low as a tuned heuristic.

### Adaptive selection

`select_adaptive` in `a_strategy.c` makes these choices:

- 2–5 values: dedicated small-input routine;
- disorder `< 0.2`: greedy insertion;
- disorder `< 0.5`: chunks;
- otherwise: radix.

This aims to use insertion on nearly ordered data, chunking at intermediate
disorder, and radix for highly disordered data. The thresholds are policy
choices and can be evaluated against operation-count measurements.

## 7. `push_swap` program flow

In `d_main.c`, `main` returns immediately if no arguments were supplied.
Otherwise it initializes both stack pointers, calls `parse_args`, then calls
`run_sort`.

`run_sort`:

1. Resets benchmark counters and enables counting only if `--bench` was
   supplied.
2. Calls `index_stack`, which assigns ranks and returns the inversion count.
3. Computes the disorder ratio.
4. Checks whether the rank sequence is already ascending.
5. Selects and runs the requested strategy only if sorting is necessary.
6. Prints the benchmark report to standard error when requested.

Finally `main` frees both linked lists. Algorithm operations are printed to
standard output, so they can be piped directly into `checker`.

## 8. `checker` program flow

`b_checker_bonus.c` first disables operation output, rejects `--` flags, and
uses the common parser to build the initial stack A. It calls `index_stack`
for duplicate validation and rank setup, then reads instructions using
`get_next_line`.

For each line, it removes one trailing newline if present, compares the
remaining string against the eleven valid instruction names, and invokes the
corresponding shared operation. An unknown or empty line triggers the
project's error path.

At end-of-input, `check_stack` checks two requirements:

- B must be empty;
- values in A must be in ascending order.

If both conditions hold it prints `OK`; otherwise it prints `KO`.

Example:

```sh
./push_swap 3 2 1 | ./checker 3 2 1
```

The first program's operation lines become the second program's standard
input.

## 9. Supporting modules

### Benchmark state

`m_benchmark.c` provides reset, enable, record, and query functions.
`m_benchmark_state.c` owns the persistent state returned by `bench_state`
and the operation-output switch. Operations increment counters only when
benchmark mode is enabled. `d_main.c` reports the disorder ratio, strategy
label, total operations, and counts by operation on standard error.

### `ft_printf`

The project's custom formatter is implemented by `ft_printf.c`,
`ft_printf_dec.c`, `ft_printf_hex.c`, and `ft_printf_float.c`. It uses a fixed
buffer and writes it to a caller-selected file descriptor. The project uses
it for benchmark reporting, particularly because benchmark output belongs
on standard error while sorting instructions belong on standard output.

Implemented conversions include `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, `%s`,
`%c`, `%%`, `%f`, and `%ld`. The float conversion prints two decimal places.
This is a project-specific formatter, not a complete replacement for the
standard `printf`.

### `get_next_line`

`ft_get_next_line.c` and `ft_get_next_line_utils.c` provide the line reader
used by the checker. It accumulates bytes in a static stash until it finds a
newline or reaches end-of-file, returns one allocated line, and preserves
any remaining bytes for the next call. The checker frees each returned line
after applying its operation.

### General utilities

`d_utils.c` contains stack cleanup, error termination, stack-size counting,
string comparison, and integer square root helpers. `clear_stack` frees all
nodes and nulls the caller's pointer; `error_exit` uses it before printing
`Error` and exiting.

## 10. Building and trying the project

Build the main program and bonus checker:

```sh
make
make bonus
```

Try each strategy:

```sh
./push_swap --simple 4 1 3 2
./push_swap --medium 4 1 3 2
./push_swap --complex 4 1 3 2
./push_swap --adaptive 4 1 3 2
```

Check a generated sequence:

```sh
./push_swap 4 1 3 2 | ./checker 4 1 3 2
```

Inspect benchmark data:

```sh
./push_swap --bench --adaptive 4 1 3 2
```

The instruction sequence goes to standard output; benchmark data goes to
standard error. Remove build products with:

```sh
make clean
make fclean
```

## 11. Suggested study sequence

For a guided code-reading session, follow this order:

1. Read `o_operations.h` and one implementation such as `o_push.c` to learn
   how a linked-list operation changes the stack.
2. Read `d_parser.c` to understand how command-line strings become nodes.
3. Trace `index_stack` in `d_index.c` and work through a small example by
   hand, recording ranks and inversions.
4. Read `d_main.c` and `a_strategy.c` to see how the program chooses a path.
5. Trace a short input through `a_sort.c`, then compare insertion, chunks,
   and radix on the same ranks.
6. Read `b_checker_bonus.c` to see how generated operations are interpreted
   independently.
7. Use `--bench` and the checker while experimenting; always verify both
   that the final stack is correct and how many operations were emitted.
