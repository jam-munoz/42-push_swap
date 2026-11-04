/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_rev_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 00:00:00 by divillan          #+#    #+#             */
/*   Updated: 2026/11/04 16:50:05 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!bench_state()->quiet)
		write(STDOUT_FILENO, "rra\n", 4);
}

void	rrb(t_stack **stack_b)
{
	rev_rotate(stack_b);
	bench_record_operation(OP_RRB);
	if (!bench_state()->quiet)
		write(STDOUT_FILENO, "rrb\n", 4);
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	bench_record_operation(OP_RRR);
	if (!bench_state()->quiet)
		write(STDOUT_FILENO, "rrr\n", 4);
}
