*This project has been created as part of the 42 curriculum by joamunoz and divillan*

<div align="center">

# `PUSH_SWAP`

### A 42 Common Core Project

<div align="center">
  <img
	src="https://raw.githubusercontent.com/divillan/42_README/main/push_swap/assets/banner.svg"
	alt="Push_swap banner"
	width="100%">
</div>

<p>
  <img src="https://img.shields.io/badge/42-Common_Core-000000?style=for-the-badge&logo=42&logoColor=white">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c">
  <img src="https://img.shields.io/badge/STATUS-FINISHED-pink?style=for-the-badge&logo=github&logoColor=white">
  <img src="https://img.shields.io/badge/Norminette-OK-green?style=for-the-badge">
</p>

**Sorting algorithms. Two stacks. Limited operations.**

A sorting challenge focused on algorithm design, optimization and problem solving in C.

[Description](#description) · [Algorithms](#algorithms) · [Checker](#checker) · [Instructions](#instructions) · [Resources](#resources) · [Authors](#authors)

</div>

---

## Description

**Push_swap** is a 42 Common Core project focused on sorting a sequence of integers using two stacks and a restricted set of operations.

The `push_swap` program receives a sequence of integers and outputs a series of instructions that sorts stack A in ascending order. Stack B is used as auxiliary storage during the process and must be empty when sorting is complete.

The challenge is not only to produce a valid sequence of operations, but also to design strategies that perform well while respecting the constraints of the instruction set.

The project also includes a `checker` executable, which reads an initial sequence and a list of instructions, applies them to the stacks, and verifies whether the final state is correctly sorted.

---

## Algorithms

### Stack operations

Both programs use the standard set of Push_swap instructions:

| Operation | Effect |
|:---:|---|
| `sa`, `sb` | Swap the top two elements of stack A or B. |
| `ss` | Apply `sa` and `sb` simultaneously. |
| `pa`, `pb` | Push the top element from one stack onto the other. |
| `ra`, `rb` | Rotate a stack upwards: its first element becomes its last. |
| `rr` | Apply `ra` and `rb` simultaneously. |
| `rra`, `rrb` | Reverse rotate a stack: its last element becomes its first. |
| `rrr` | Apply `rra` and `rrb` simultaneously. |

An operation on a stack with fewer than two elements leaves that stack unchanged.

### Parsing and indexing

Before sorting begins, the input is validated and stored in a linked-list-based stack structure.

The indexing stage orders pointers to the stack elements using **merge sort**, then assigns each value a zero-based rank:

- The smallest value receives rank `0`.
- The next smallest receives rank `1`.
- The largest value receives rank `n - 1`.

The original integers remain stored in the stack; their ranks are used by the sorting strategies. This normalization makes the algorithms independent of the actual magnitude or sign of the input values and is particularly useful for radix sort.

Duplicate values and invalid input are rejected.

The merge-sort process also provides a measure of input disorder. This value is used by the adaptive strategy to choose an appropriate sorting approach.

### Sorting strategies

The project implements three main sorting strategies, alongside an adaptive mode.

#### Simple — Greedy insertion (`--simple`)

The insertion strategy builds stack B in circular descending order.

1. It moves an initial element from A to B.
2. For every remaining element in A, it determines the appropriate insertion position in B.
3. It evaluates the rotations required to bring the element and its target position to the top of their respective stacks.
4. It considers forward and reverse rotations, including combined `rr` and `rrr` operations, and selects the candidate with the lowest estimated cost.
5. Once all elements have been transferred, it brings the largest rank to the top of B and pushes the elements back to A.

This greedy approach aims to reduce unnecessary rotations by choosing the most convenient insertion at each step. Its performance depends on the initial arrangement of the input.

#### Medium — Chunk strategy (`--medium`)

The chunk strategy divides the ranked input into progressively processed ranges.

1. It calculates a chunk width based approximately on the square root of the input size.
2. It scans stack A and transfers elements belonging to the current rank range to B.
3. Elements at the lower end of the current range are rotated in B, helping keep higher ranks accessible.
4. After transferring all elements, it repeatedly finds the largest remaining rank in B, rotates it to the top using the shorter direction, and pushes it back to A.

Chunking balances the work involved in scanning A and reorganizing B. The resulting sequence depends on the input order.

#### Complex — Binary radix (`--complex`)

The radix strategy sorts the normalized ranks by processing their binary representation, one bit at a time, from least significant to most significant.

For each bit position:

1. It scans stack A.
2. Elements whose current bit is `1` are rotated in A.
3. Elements whose current bit is `0` are pushed to B.
4. Once the pass is complete, all elements are pushed back from B to A.

Because the ranks are non-negative and bounded by the input size, radix provides predictable `O(n log n)` time complexity and is well suited to larger, highly disordered inputs.

### Adaptive strategy (`--adaptive`)

Adaptive mode is the default when no strategy flag is provided.

For inputs of two to five elements, the program uses dedicated small-stack routines. For larger inputs, it evaluates the input disorder and selects a strategy:

| Input disorder | Selected strategy |
|---|---|
| Below `0.2` | Greedy insertion |
| From `0.2` to below `0.5` | Chunk |
| `0.5` or above | Binary radix |

The goal is to match the strategy to the structure of the input: insertion for nearly ordered sequences, chunks for intermediate cases, and radix for highly disordered sequences.

---

## Checker

The bonus executable, `checker`, validates a sequence of Push_swap instructions.

It receives the same initial integer sequence as `push_swap`, reads instructions from standard input, and applies them to stacks A and B.

After the input stream ends, it checks that:

- Stack A is sorted in ascending order.
- Stack B is empty.

It prints `OK` when both conditions are satisfied and `KO` otherwise. Invalid instructions are treated as errors.

---

## Instructions

### Build

Compile the mandatory program and the bonus checker:

```sh
make
make bonus
```

This creates two executables:

- `push_swap`
- `checker`

### Run the sorter

```sh
./push_swap [--simple|--medium|--complex|--adaptive] <numbers...>
```

The strategy flag is optional. If omitted, the adaptive strategy is used.

Numbers can be passed as separate arguments or as a single space-separated string:

```sh
./push_swap 3 2 1
./push_swap "--medium" "8 -3 0 42"
./push_swap --complex 9 4 7 1 5 2
```

### Check a sequence

Pipe the output of `push_swap` into `checker`, passing the same initial values to both programs:

```sh
./push_swap 3 2 1 | ./checker 3 2 1
```

The checker reads instructions until the input stream ends. It can also be used manually:

```sh
./checker 3 2 1
sa
rra
```

Finish the input with `Ctrl+D` (Linux/macOS terminal).

### Clean build files

Remove object files:

```sh
make clean
```

Remove object files and executables:

```sh
make fclean
```

Rebuild the project from scratch:

```sh
make re
```

---

## Resources

- **K. N. King, _C Programming: A Modern Approach_**
  - Chapter 15: Writing Large Programs
	- 15.1 Source Files
	- 15.2 Header Files
	- 15.3 Dividing a Program into Files
	- 15.4 Building a Multiple-File Program
  - Chapter 16: Structures, Unions, and Enumerations
	- 16.1 Structure Variables
	- 16.2 Structure Types
  - Chapter 17: Advanced Uses of Pointers
	- 17.1 Dynamic Storage Allocation
	- 17.4 Deallocating Storage
	- 17.5 Linked Lists
	- 17.6 Pointers to Pointers
  - Chapter 9.6: Recursion
- **CS50x**
  - [Week 3: Algorithms](https://cs50.harvard.edu/x/weeks/3/)
- **42**
  - Push_swap subject and project requirements.

---

## Authors

This project was developed collaboratively by **joamunoz** and **divillan** as part of the 42 Common Core curriculum.

The work began with an initial division of focus:

| Contributor | Initial area of focus |
|---|---|
| **joamunoz** | Parsing, input validation and indexing. |
| **divillan** | Design and implementation of the sorting strategies and algorithms. |

Once the initial components were working together and the project had reached a functional state, development moved into a shared refinement phase. Both contributors worked across the codebase to improve, optimize and adapt the existing implementation, as well as to integrate the different components.

Consequently, the areas above describe the **initial distribution of work**, not exclusive ownership of specific files or features. The final implementation is the result of joint development and collaboration.
