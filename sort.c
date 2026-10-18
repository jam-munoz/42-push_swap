/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:50:10 by divillan          #+#    #+#             */
/*   Updated: 2026/10/18 18:50:44 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_to_position(t_stack **stack_a, int index)
{
	int		size;
	int		pos;
	t_stack	*tmp;

	pos = 0;
	tmp = *stack_a;
	while (tmp)
	{
		if (tmp->index == index)
			break ;
		tmp = tmp->next;
		pos++;
	}
	size = get_stack_size(*stack_a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(stack_a);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			rra(stack_a);
	}
}

void	two_sort(t_stack **stack_a)
{
	sa(stack_a);
}

void	three_sort(t_stack **stack_a, int i)
{
	int	a;
	int	b;

	a = (*stack_a)->index - i;
	b = (*stack_a)->next->index - i;

	if (a == 0 && b == 1)
		return ;
	else if (a == 0 && b == 2)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (a == 1 && b == 0)
		sa(stack_a);
	else if (a == 1 && b == 2)
		rra(stack_a);
	else if (a == 2 && b == 0)
		ra(stack_a);
	else
	{
		sa(stack_a);
		rra(stack_a);
	}
}


void	four_sort(t_stack **stack_a, t_stack **stack_b)
{
	rotate_to_position(stack_a, 0);
	pb(stack_a, stack_b);
	three_sort(stack_a, 1);
	pa(stack_a, stack_b);
}

void	five_sort(t_stack **stack_a, t_stack **stack_b)
{
	rotate_to_position(stack_a, 0);
	pb(stack_a, stack_b);
	rotate_to_position(stack_a, 1);
	pb(stack_a, stack_b);
	three_sort(stack_a, 2);
	pa(stack_a, stack_b);
	pa(stack_a, stack_b);

}
