/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/04 16:02:07 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

static void	push(t_stack **stack_1, t_stack **stack_2)
{
	t_stack	*temp;

	if (!stack_1 || !*stack_1 || !(*stack_1)->next)
		return ;
	temp = (*stack_1)->next;
	(*stack_1)->next = *stack_2;
	*stack_2 = *stack_1;
	*stack_1 = temp;
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_b, stack_a);
	write(STDOUT_FILENO, "pa\n", 3);
}

void	pb(t_stack **stack_b, t_stack **stack_a)
{
	push(stack_a, stack_b);
	write(STDOUT_FILENO, "pb\n", 3);
}
