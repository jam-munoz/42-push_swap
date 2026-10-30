/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:04:14 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "o_operations.h"
#include "d_push_swap.h"

static void	rotate(t_stack **stack)
{
	t_stack	*temp;
	t_stack	*rot;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	temp = (*stack)->next;
	rot = temp;
	while (rot->next != NULL)
		rot = rot->next;
	rot->next = *stack;
	(*stack)->next = NULL;
	*stack = temp;
}

void	ra(t_stack **stack_a)
{
	rotate(stack_a);
	bench_record_operation(OP_RA);
	write_operation("ra\n", 3);
}

void	rb(t_stack **stack_b)
{
	rotate(stack_b);
	bench_record_operation(OP_RB);
	write_operation("rb\n", 3);
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	bench_record_operation(OP_RR);
	write_operation("rr\n", 3);
}
