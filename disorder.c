/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 20:33:58 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/13 20:34:04 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	count_inversions(t_stack *stack)
{
	t_stack	*other;
	long	count;

	count = 0;
	while (stack)
	{
		other = stack->next;
		while (other)
		{
			if (stack->index > other->index)
				count++;
			other = other->next;
		}
		stack = stack->next;
	}
	return (count);
}

float	compute_disorder(t_stack *stack)
{
	long	size;
	long	pairs;

	size = get_stack_size(stack);
	pairs = size * (size - 1) / 2;
	if (pairs == 0)
		return (0);
	return ((float)count_inversions(stack) / pairs);
}

