/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_insertion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 22:56:12 by divillan          #+#    #+#             */
/*   Updated: 2026/10/30 22:56:15 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

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

static void	rotate_b_to_position(t_stack **stack_b, int position)
{
	int	size;

	size = get_stack_size(*stack_b);
	if (position <= size / 2)
	{
		while (position-- > 0)
			rb(stack_b);
	}
	else
	{
		position = size - position;
		while (position-- > 0)
			rrb(stack_b);
	}
}

static void	restore_stack(t_stack **stack_a, t_stack **stack_b)
{
	int	position;

	position = find_max_position(*stack_b);
	rotate_b_to_position(stack_b, position);
	while (*stack_b)
		pa(stack_a, stack_b);
}

void	insertion_sort(t_stack **stack_a, t_stack **stack_b)
{
	t_insertion_move	move;

	if (!stack_a || !stack_b || !*stack_a)
		return ;
	pb(stack_a, stack_b);
	while (*stack_a)
	{
		find_best_insertion(*stack_a, *stack_b, &move);
		apply_insertion_rotations(stack_a, stack_b, move);
		pb(stack_a, stack_b);
	}
	restore_stack(stack_a, stack_b);
}
