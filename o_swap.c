/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_swap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:04:19 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "o_operations.h"
#include "d_push_swap.h"

static void	swap(t_stack **stack)
{
	t_stack	*temp;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	temp = (*stack)->next;
	(*stack)->next = temp->next;
	temp->next = *stack;
	*stack = temp;
}

void	sa(t_stack **stack_a)
{
	swap(stack_a);
	bench_record_operation(OP_SA);
	write(STDOUT_FILENO, "sa\n", 3);
}

void	sb(t_stack **stack_b)
{
	swap(stack_b);
	bench_record_operation(OP_SB);
	write(STDOUT_FILENO, "sb\n", 3);
}

void	ss(t_stack **stack_a, t_stack **stack_b)
{
	swap(stack_a);
	swap(stack_b);
	bench_record_operation(OP_SS);
	write(STDOUT_FILENO, "ss\n", 3);
}
