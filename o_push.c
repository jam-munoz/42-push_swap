/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_push.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:04:09 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "o_operations.h"
#include "d_push_swap.h"

static void	push(t_stack **stack_1, t_stack **stack_2)
{
	t_stack	*temp;

	if (!stack_1 || !*stack_1)
		return ;
	temp = (*stack_1)->next;
	(*stack_1)->next = *stack_2;
	*stack_2 = *stack_1;
	*stack_1 = temp;
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_b, stack_a);
	bench_record_operation(OP_PA);
	write(STDOUT_FILENO, "pa\n", 3);
}

void	pb(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_a, stack_b);
	bench_record_operation(OP_PB);
	write(STDOUT_FILENO, "pb\n", 3);
}
