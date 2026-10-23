/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/23 20:00:00 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
