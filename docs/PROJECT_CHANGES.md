# Project Changes

This document records changes made during the Push_swap review and preserves
two historical versions of insertion: the original implementation from before
the greedy changes, and the intermediate single-file greedy implementation
from before the source-file-limit refactor. Neither backup is compiled by the
current Makefile. The active implementation is in `a_insertion.c`,
`a_insertion_cost.c`, and `a_insertion_moves.c`.

## Changes made

### Checker and operations

- Operation functions used by `push_swap` print instructions directly.
  An earlier output-suppression switch was removed because it relied on a
  file-scope global variable; `checker` now applies instructions through its
  own silent stack helpers in `b_checker_utils_bonus.c`.
- Changed checker instruction parsing to accept a final instruction without
  a trailing newline.
- Changed blank instruction lines to be rejected as invalid instructions
  instead of treating them as end-of-input.

### Input parsing

- Added a pre-multiplication range check when parsing integer digits. This
  rejects values outside the `int` range, including very long numbers, before
  the accumulation can overflow.

### Benchmark formatting

- Added `%ld` formatting to the project's `ft_printf` implementation.
- Updated benchmark operation counters to use `%ld` for their `long` values.
- Distributed the benchmark query functions across `m_benchmark.c` and
  `m_benchmark_state.c`, keeping each source file within the function limit.

### Strategy information and build configuration

- Corrected the medium strategy's displayed complexity label from `O(n√2)`
  to `O(n√n)`.
- Marked the `bonus` Make target as phony.
- Updated `.gitignore` to ignore the generated `checker` executable.
- Added build, run, checker, benchmark, and cleanup instructions to the README.

### README documentation

- Replaced the placeholder algorithm section with an explanation of stack
  operations, rank compression, inversion-based disorder measurement, and the
  simple, medium, complex, and adaptive strategies.
- Added project instructions and restored the full list of book subsections,
  recursion, and the CS50x Week 3 resource.

### Greedy insertion

- Changed insertion from always moving the top of A to evaluating every
  remaining A element before each push.
- For each candidate, calculate its insertion position in circular descending
  order in B and the rotations needed in both stacks.
- Compare forward and reverse rotations and account for shared `rr`/`rrr`
  operations when both stacks rotate in the same direction.
- Apply the candidate's shared rotations first, then its remaining individual
  rotations, and push it to B.
- Documented this greedy approach and its trade-off: it reduces local move
  costs but does not guarantee a globally minimal sequence.

### Source-file constraint refactor

- Split the greedy implementation across three `.c` files to meet the
  requirement of no more than five functions and 25 lines per function:
  - `a_insertion.c`: top-level insertion flow and stack restoration.
  - `a_insertion_cost.c`: insertion-position and candidate-cost calculations.
  - `a_insertion_moves.c`: execution of combined and individual rotations.
- The insertion `.c` files contain no struct definitions. Their shared
  `t_insertion_move` declaration and function prototypes are in
  `d_push_swap.h`.
- Added stack sizes to the move context so the candidate evaluator does not
  need more than four function arguments.
- Added the new sources and header dependency to the Makefile.

### Norminette-related refactors

- Removed the file-scope operation-output variable introduced for checker
  suppression. The checker uses silent stack mutations instead, and
  `b_checker_utils_bonus.c` now contains those helpers.
- Kept integer token parsing in `d_parser.c` by condensing its checked
  accumulation logic, retaining the function-count and line limits without
  adding a parser source or header.
- Kept format conversion dispatch in `ft_printf.c`; reorganized its helpers
  to stay within the source-file function and function-length limits without
  a separate conversion source.
- Kept checker setup, instruction processing, and final validation within
  the source-file function and line limits.

### Keeping the file count down

- Removed the temporary `d_parser_numbers.c`, `d_parser_numbers.h`, and
  `ft_printf_conv.c` modules after confirming their logic could remain in the
  existing parser and formatter files while still passing Norminette.
- Removed the insertion-only `a_insertion.h`; its shared type and prototypes
  now live in the existing `d_push_swap.h`.

## Original `insertion.c` before any changes in this session

This is the version that was in `a_insertion.c` before the greedy insertion
implementation was introduced. It processes the current top of A each time:
finds its insertion point in B, rotates B there, and pushes that value. It is
the original implementation requested as a fallback and is not compiled by
the current Makefile.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 11:58:57 by divillan          #+#    #+#             */
/*   Updated: 2026/10/09 14:44:49 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

static int	find_insertion_position(t_stack *stack, int index)
{
	t_stack	*first;
	t_stack	*next;
	int		pos;

	first = stack;
	pos = 0;
	while (stack)
	{
		next = stack->next;
		if (!next)
			next = first;
		if (stack->index < next->index
			&& (index < stack->index || index > next->index))
			return (pos + 1);
		if (stack->index > index && index > next->index)
			return (pos + 1);
		pos++;
		stack = stack->next;
	}
	return (0);
}

static int	find_max_position(t_stack *stack)
{
	int	pos;
	int	max_index;

	pos = 0;
	max_index = get_stack_size(stack) - 1;
	while (stack)
	{
		if (stack->index == max_index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}

static void	rotate_to_position(t_stack **stack, int position)
{
	int	size;

	if (!stack || !*stack)
		return ;
	size = get_stack_size(*stack);
	if (size <= 1)
		return ;
	if (position <= size / 2)
	{
		while (position-- > 0)
			rb(stack);
	}
	else
	{
		position = size - position;
		while (position-- > 0)
			rrb(stack);
	}
}

void	insertion_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	position;

	if (!stack_a || !stack_b || !*stack_a)
		return ;
	pb(stack_a, stack_b);
	while (*stack_a)
	{
		position = find_insertion_position(*stack_b, (*stack_a)->index);
		rotate_to_position(stack_b, position);
		pb(stack_a, stack_b);
	}
	position = find_max_position(*stack_b);
	rotate_to_position(stack_b, position);
	while (*stack_b)
		pa(stack_a, stack_b);
}
```
