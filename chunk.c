/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 15:35:53 by divillan          #+#    #+#             */
/*   Updated: 2026/10/09 15:00:38 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	chunk_to_postion(t_stack **stack_a, t_stack **stack_b)
{
	int	chunk;
	int	chunk_size;
	int	counter;

	chunk = 0;
	chunk_size = ft_sqrt(get_stack_size(*stack_a));
	counter = 0;
	while (*stack_a)
	{
		if ((*stack_a)->index >= (chunk * chunk_size)
			&& (*stack_a)->index < ((chunk + 1) * chunk_size))
		{
			pb(stack_a, stack_b);
			counter++;
		}
		else
			ra(stack_a);
		if (counter == chunk_size)
		{
			chunk++;
			counter = 0;
		}
	}
}

int	find_index_position(t_stack *stack, int index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (0);
}

void	rotate_to_position(t_stack **stack, int position)
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

void	chunk_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	max;

	max = get_stack_size(*stack_b) - 1;
	chunk_to_postion(stack_a, stack_b);
	while (*stack_b)
	{
		rotate_to_position(stack_b, find_index_position(*stack_b, max));
		pa(stack_a, stack_b);
		max--;
	}
}
