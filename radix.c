/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:46:13 by divillan          #+#    #+#             */
/*   Updated: 2026/10/06 15:52:23 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(int index)
{
	int	max_bits;

	max_bits = 0;
	while (index)
	{
		index >>= 1;
		max_bits++;
	}

	return (max_bits);
}

void	radix_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	bit;
	int	i;
	int	max_bits;
	int	size;

	bit = 0;
	size = get_stack_size(*stack_a);
	max_bits = get_max_bits(size - 1);
	while (bit < max_bits)
	{
		i = 0;
		while (i < size)
		{
			if ((((*stack_a)->index >> bit) & 1) == 1)
				ra(stack_a);
			else
				pb(stack_b, stack_a);
			i++;
		}
		while (*stack_b)
			pa(stack_a, stack_b);
		bit++;
	}
}
