/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_insertion_cost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 22:54:25 by divillan          #+#    #+#             */
/*   Updated: 2026/10/30 22:54:44 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

static int	find_insert_position(t_stack *stack, int index)
{
	t_stack	*first;
	t_stack	*next;
	int		position;

	first = stack;
	position = 0;
	while (stack)
	{
		next = stack->next;
		if (!next)
			next = first;
		if (stack->index < next->index
			&& (index < stack->index || index > next->index))
			return (position + 1);
		if (stack->index > index && index > next->index)
			return (position + 1);
		position++;
		stack = stack->next;
	}
	return (0);
}

static int	rotation_cost(int a_rotations, int b_rotations)
{
	int	a_cost;
	int	b_cost;

	a_cost = a_rotations;
	b_cost = b_rotations;
	if (a_cost < 0)
		a_cost = -a_cost;
	if (b_cost < 0)
		b_cost = -b_cost;
	if ((a_rotations > 0 && b_rotations > 0)
		|| (a_rotations < 0 && b_rotations < 0))
	{
		if (a_cost > b_cost)
			return (a_cost);
		return (b_cost);
	}
	return (a_cost + b_cost);
}

static void	save_candidate(t_insertion_move *best, int a_rot, int b_rot)
{
	int	total;

	total = rotation_cost(a_rot, b_rot);
	if (!best->found || total < best->total)
	{
		best->a_rotations = a_rot;
		best->b_rotations = b_rot;
		best->total = total;
		best->found = 1;
	}
}

static void	consider_candidate(t_insertion_move *best, int a_pos, int b_pos)
{
	save_candidate(best, a_pos, b_pos);
	save_candidate(best, a_pos, b_pos - best->size_b);
	save_candidate(best, a_pos - best->size_a, b_pos);
	save_candidate(best, a_pos - best->size_a, b_pos - best->size_b);
}

void	find_best_insertion(t_stack *stack_a, t_stack *stack_b,
		t_insertion_move *best)
{
	int	size_a;
	int	size_b;
	int	a_pos;

	best->found = 0;
	best->total = 0;
	size_a = get_stack_size(stack_a);
	size_b = get_stack_size(stack_b);
	best->size_a = size_a;
	best->size_b = size_b;
	a_pos = 0;
	while (stack_a)
	{
		consider_candidate(best, a_pos,
			find_insert_position(stack_b, stack_a->index));
		stack_a = stack_a->next;
		a_pos++;
	}
}
