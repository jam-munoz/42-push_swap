/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/11/04 00:00:00 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"

int	apply_checker_instruction(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp(instruction, "sa") == 0)
		sa(stack_a);
	else if (ft_strcmp(instruction, "sb") == 0)
		sb(stack_b);
	else if (ft_strcmp(instruction, "ss") == 0)
		ss(stack_a, stack_b);
	else if (ft_strcmp(instruction, "pa") == 0)
		pa(stack_a, stack_b);
	else if (ft_strcmp(instruction, "pb") == 0)
		pb(stack_a, stack_b);
	else if (ft_strcmp(instruction, "ra") == 0)
		ra(stack_a);
	else if (ft_strcmp(instruction, "rb") == 0)
		rb(stack_b);
	else if (ft_strcmp(instruction, "rr") == 0)
		rr(stack_a, stack_b);
	else if (ft_strcmp(instruction, "rra") == 0)
		rra(stack_a);
	else if (ft_strcmp(instruction, "rrb") == 0)
		rrb(stack_b);
	else if (ft_strcmp(instruction, "rrr") == 0)
		rrr(stack_a, stack_b);
	else
		return (0);
	return (1);
}
