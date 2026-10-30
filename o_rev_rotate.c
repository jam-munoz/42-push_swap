/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_rev_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:04:11 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "o_operations.h"
#include "d_push_swap.h"

static void	rev_rotate(t_stack **stack)
{
	t_stack	*temp;
	t_stack	*rot;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	rot = *stack;
	while (rot->next->next != NULL)
		rot = rot->next;
	temp = rot->next;
	rot->next = NULL;
	temp->next = *stack;
	*stack = temp;
}

void	rra(t_stack **stack_a)
{
	rev_rotate(stack_a);
	bench_record_operation(OP_RRA);
	write_operation("rra\n", 4);
}

void	rrb(t_stack **stack_b)
{
	rev_rotate(stack_b);
	bench_record_operation(OP_RRB);
	write_operation("rrb\n", 4);
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	bench_record_operation(OP_RRR);
	write_operation("rrr\n", 4);
}
