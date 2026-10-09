/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 11:58:57 by divillan          #+#    #+#             */
/*   Updated: 2026/10/09 14:35:55 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		if (stack->index > index && index > next->index)
			return (pos + 1);
		if (stack->index < next->index
			&& (index > stack->index || index < next->index))
			return (pos);
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

	size = get_stack_size(*stack);
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
