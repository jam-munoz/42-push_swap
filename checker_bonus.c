/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/23 20:00:00 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	check_instructions(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp("sa\n", instruction) == 0)
		sa(stack_a);
	else if (ft_strcmp("sb\n", instruction) == 0)
		sb(stack_b);
	else if (ft_strcmp("ss\n", instruction) == 0)
		ss(stack_a, stack_b);
	else if (ft_strcmp("pa\n", instruction) == 0)
		pa(stack_a, stack_b);
	else if (ft_strcmp("pb\n", instruction) == 0)
		pb(stack_a, stack_b);
	else if (ft_strcmp("ra\n", instruction) == 0)
		ra(stack_a);
	else if (ft_strcmp("rb\n", instruction) == 0)
		rb(stack_b);
	else if (ft_strcmp("rr\n", instruction) == 0)
		rr(stack_a, stack_b);
	else
		check_reverse_instruction(instruction, stack_a, stack_b);
}

void	check_stack(t_stack *stack_a)
{
	t_stack	*prev;

	while (stack_a->next != NULL)
	{
		prev = stack_a;
		stack_a = stack_a->next;
		if (prev->number > stack_a->number)
		{
			write(STDOUT_FILENO, "KO\n", 3);
			return ;
		}
	}
	write(STDOUT_FILENO, "OK\n", 3);
}
