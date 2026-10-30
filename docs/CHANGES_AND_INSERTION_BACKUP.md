# Project changes and insertion backup

This document records changes made during the Push_swap review and preserves
two historical versions of insertion: the original implementation from before
the greedy changes, and the intermediate single-file greedy implementation
from before the source-file-limit refactor. Neither backup is compiled by the
current Makefile. The active implementation is in `a_insertion.c`,
`a_insertion_cost.c`, and `a_insertion_moves.c`.

## Changes made

### Checker and operations

- Added a switch to enable or suppress operation output. `push_swap` keeps
  printing operations, while `checker` applies them silently and prints only
  its final result.
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
- Moved the shared `t_insertion_move` structure declaration into
  `a_insertion.h`; no `.c` file defines a struct.
- Added the new sources and header dependency to the Makefile.

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

/*
	BUCKET A = Disordered
	BUCKET B = Ordered

	pb(A[0])

	Comparation loop to find where to insert next element
	LOOP:	SAVE:	-Look for the best lower
					-Save best possible candidate
			RETURN:	-Insertion position

	Calculate distance and select the cheaper one
	rb VS rrb

	pb

	REPEAT

	When no elements in BUCKET A
	Search for element index N - 1 = MAX_ELEMENT
	Put MAX_ELEMENT on TOP
	rb VS rrb
	pa -> All Elements
*/

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
