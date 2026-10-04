/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:29:40 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/04 16:01:39 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

static void	swap(t_stack **stack)
{
	t_stack	*temp;

	//proteger casos borde: sobre un stack de 0 o 1 elementos no debería hacer nada.
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
	write(STDOUT_FILENO, "sa\n", 3);
}

void	sb(t_stack **stack_b)
{
	swap(stack_b);
	write(STDOUT_FILENO, "sb\n", 3);
}

void	ss(t_stack **stack_a, t_stack **stack_b)
{
	swap(stack_a);
	swap(stack_b);
	write(STDOUT_FILENO, "ss\n", 3);
}
