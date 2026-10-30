/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_insertion_moves.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 22:55:07 by divillan          #+#    #+#             */
/*   Updated: 2026/10/30 22:55:11 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

static void	apply_shared_rotations(t_stack **stack_a, t_stack **stack_b,
		t_insertion_move *move)
{
	while (move->a_rotations > 0 && move->b_rotations > 0)
	{
		rr(stack_a, stack_b);
		move->a_rotations--;
		move->b_rotations--;
	}
	while (move->a_rotations < 0 && move->b_rotations < 0)
	{
		rrr(stack_a, stack_b);
		move->a_rotations++;
		move->b_rotations++;
	}
}

static void	rotate_a(t_stack **stack_a, int rotations)
{
	while (rotations > 0)
	{
		ra(stack_a);
		rotations--;
	}
	while (rotations < 0)
	{
		rra(stack_a);
		rotations++;
	}
}

static void	rotate_b(t_stack **stack_b, int rotations)
{
	while (rotations > 0)
	{
		rb(stack_b);
		rotations--;
	}
	while (rotations < 0)
	{
		rrb(stack_b);
		rotations++;
	}
}

void	apply_insertion_rotations(t_stack **stack_a, t_stack **stack_b,
		t_insertion_move move)
{
	apply_shared_rotations(stack_a, stack_b, &move);
	rotate_a(stack_a, move.a_rotations);
	rotate_b(stack_b, move.b_rotations);
}
