/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/04 16:01:27 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

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
	write(STDOUT_FILENO, "rra\n", 4);
}

void	rrb(t_stack **stack_b)
{
	rev_rotate(stack_b);
	write(STDOUT_FILENO, "rrb\n", 4);
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	write(STDOUT_FILENO, "rrr\n", 4);
}
