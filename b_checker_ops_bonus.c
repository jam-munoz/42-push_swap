/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/24 08:06:56 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"

void	check_reverse_instruction(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp("rra\n", instruction) == 0)
		rra(stack_a);
	else if (ft_strcmp("rrb\n", instruction) == 0)
		rrb(stack_b);
	else if (ft_strcmp("rrr\n", instruction) == 0)
		rrr(stack_a, stack_b);
	else
	{
		clear_stack(stack_b);
		error_exit(stack_a);
	}
}
