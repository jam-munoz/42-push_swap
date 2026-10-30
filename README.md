*This project has been created as part of the 42 curriculum by joamunoz and divillan*

 <div align="center">

# `PUSH_SWAP`

### A 42 Common Core Project

  <div align="center">
    <img  src="https://raw.githubusercontent.com/divillan/42_README/main/push_swap/assets/banner.svg"
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

<br>

[Description](#description) · [Algorithms](#algorithms) · [Instructions](#instructions) · [Resources](#resources) · [Authors](#authors)

</div>

---

## Description

**Push_swap** is a 42 Common Core project about sorting integers with two stacks and a restricted instruction set. The `push_swap` program reads a sequence of integers and prints a sequence of operations that sorts them in ascending order in stack A, using as few operations as practical. Stack B is an auxiliary stack and must be empty at the end.

The project also includes `checker`, which reads an initial sequence and a list of operations, applies them, and reports whether the final state is sorted correctly.

For a detailed walkthrough of the architecture, parsing, ranking, algorithms,
operations, and checker, see the [project study guide](docs/PROJECT_STUDY_GUIDE.md).

---

## Algorithms

### Stack operations

The programs use the standard push_swap operations:

| Operation | Effect |
|---|---|
| `sa`, `sb` | Swap the top two elements of stack A or B. |
| `ss` | Apply `sa` and `sb` together. |
| `pa`, `pb` | Push the top element from one stack onto the other. |
| `ra`, `rb` | Rotate a stack upwards: its first element becomes its last. |
| `rr` | Apply `ra` and `rb` together. |
| `rra`, `rrb` | Reverse rotate a stack: its last element becomes its first. |
| `rrr` | Apply `rra` and `rrb` together. |

An operation on a stack with fewer than two elements leaves that stack unchanged.

### Ranking the input

Before selecting a sorting strategy, `push_swap` sorts pointers to the input values with merge sort and assigns each value a zero-based rank. The smallest value gets rank `0`, the next gets rank `1`, and so on. The original integers are preserved in the stack; the ranks make comparisons independent of their magnitude and allow radix sort to work with negative and widely spaced input values. Duplicate values are rejected.

The same merge-sort pass counts inversions: pairs of values that are out of ascending order. The program divides this count by the maximum possible number of inversions to estimate input disorder, from `0` (already sorted) to `1` (reverse sorted). If the stack is already sorted, no sorting operations are emitted.

### Available strategies

The strategy can be selected with a command-line mode:

* **Simple (`--simple`) — greedy insertion strategy.** It starts by pushing one value from A to B, then keeps B in circular descending order. For every remaining value in A, it finds the position where that value can be inserted into B and estimates the rotations needed to bring both the value and its insertion position to the top. It considers forward and reverse rotations on both stacks, including combined `rr`/`rrr` moves, and chooses the candidate with the lowest estimated operation count. After pushing all values to B, it rotates the largest rank to the top and moves the values back to A. This greedy choice reduces unnecessary rotations compared with always inserting the top of A, though finding the cheapest candidate at each step still involves repeated scans and does not guarantee a globally minimal sequence.
* **Medium (`--medium`) — chunk strategy.** The algorithm uses a moving rank window whose width is approximately the square root of the input size. While scanning A, it pushes ranks within the current window to B and advances the window as values are transferred. Ranks at the lower edge are rotated down in B to help keep larger ranks accessible. After all ranks have been transferred, it repeatedly locates the largest remaining rank in B, rotates it to the top using the shorter direction, and pushes it back to A. Chunking aims to balance the number of scans and rotations; the actual move count depends on the input order.
* **Complex (`--complex`) — binary radix strategy.** The algorithm processes the rank bits from least significant to most significant. For each bit, it scans A once: ranks with a `1` bit are rotated in A, and ranks with a `0` bit are pushed to B. It then pushes all values back from B to A before processing the next bit. Because ranks are non-negative and bounded by the input size, this produces a predictable `O(n log n)` number of operations, where `n` is the number of values.
* **Adaptive (`--adaptive`, the default).** Inputs of two to five elements use dedicated small-stack routines. Larger inputs use the measured disorder to choose insertion for disorder below `0.2`, chunks below `0.5`, and radix otherwise. This aims to use the simpler strategy for nearly ordered inputs and the more predictable radix strategy for highly disordered inputs.

The strategy names describe their intended trade-offs; the number of emitted operations is input-dependent, especially for insertion and chunks. Use `--bench` to inspect the measured disorder, selected strategy, and operation counts for a run.

---

## Instructions

### Build

```sh
make
make bonus
```

This creates `push_swap` and the bonus executable `checker`.

### Run the sorter

```sh
./push_swap [--simple|--medium|--complex|--adaptive] [--bench] <numbers...>
```

Provide the integers as separate arguments or as a space-separated string:

```sh
./push_swap 3 2 1
./push_swap "--medium" "8 -3 0 42"
```

The mode and `--bench` flag, if used, must appear before the numbers. The default mode is `--adaptive`. `--bench` writes its report to standard error, leaving the operation sequence on standard output.

### Check a sequence

Pass the same initial values to `checker` and pipe the operations into it:

```sh
./push_swap 3 2 1 | ./checker 3 2 1
```

`checker` reads one operation per line from standard input and prints `OK` if stack A is in ascending order and stack B is empty; otherwise it prints `KO`. An unknown or empty instruction is an error.

### Clean build files

```sh
make clean
make fclean
```

---

## Resources

* K. N. King, *C Programming: A Modern Approach*
  * Chapter 15: Writing Large Programs
    * 15.1 Source Files
    * 15.2 Header Files
    * 15.3 Dividing a Program into Files
    * 15.4 Building a Multiple-File Program
  * Chapter 16: Structures, Unions, and Enumerations
    * 16.1 Structure Variables
    * 16.2 Structure Types
  * Chapter 17: Advanced Uses of Pointers
    * 17.1 Dynamic Storage Allocation
    * 17.4 Deallocating Storage
    * 17.5 Linked Lists
    * 17.6 Pointers to Pointers
  * Chapter 9.6: Recursion
* CS50x, [Week 3: Algorithms](https://cs50.harvard.edu/x/weeks/3/)

## Authors

This project was created as part of the 42 curriculum by **joamunoz** and **divillan**.
