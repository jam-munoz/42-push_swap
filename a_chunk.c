/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_chunk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 15:35:53 by divillan          #+#    #+#             */
/*   Updated: 2026/10/25 07:06:24 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

static int	find_index_position(t_stack *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}

static void	rotate_b_to_position(t_stack **stack_b, int position)
{
	int	size;

	if (!stack_b || !*stack_b || position <= 0)
		return ;
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

static void	push_chunks(t_stack **stack_a, t_stack **stack_b, int chunk_size)
{
	int	next_index;

	next_index = 0;
	while (*stack_a)
	{
		if ((*stack_a)->index <= next_index)
		{
			pb(stack_a, stack_b);
			rb(stack_b);
			next_index++;
		}
		else if ((*stack_a)->index <= next_index + chunk_size)
		{
			pb(stack_a, stack_b);
			next_index++;
		}
		else
			ra(stack_a);
	}
}

void	chunk_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	chunk_size;
	int	max_index;
	int	position;

	if (!stack_a || !stack_b || !*stack_a)
		return ;
	size = get_stack_size(*stack_a);
	if (size <= 1)
		return ;
	chunk_size = ft_sqrt(size);
	if (chunk_size < 2)
		chunk_size = 2;
	push_chunks(stack_a, stack_b, chunk_size);
	max_index = size - 1;
	while (*stack_b)
	{
		position = find_index_position(*stack_b, max_index);
		rotate_b_to_position(stack_b, position);
		pa(stack_a, stack_b);
		max_index--;
	}
}
