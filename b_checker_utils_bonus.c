/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 17:32:55 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"

static void	change_stack(t_stack **source, t_stack **destination, int push)
{
	t_stack	*node;

	if (!source || !*source)
		return ;
	if (push)
	{
		node = *source;
		*source = node->next;
		node->next = *destination;
		*destination = node;
	}
	else if ((*source)->next)
	{
		node = (*source)->next;
		(*source)->next = node->next;
		node->next = *source;
		*source = node;
	}
}

static int	apply_push_swap(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp(instruction, "sa") == 0)
		change_stack(stack_a, NULL, 0);
	else if (ft_strcmp(instruction, "sb") == 0)
		change_stack(stack_b, NULL, 0);
	else if (ft_strcmp(instruction, "ss") == 0)
		(change_stack(stack_a, NULL, 0), change_stack(stack_b, NULL, 0));
	else if (ft_strcmp(instruction, "pa") == 0)
		change_stack(stack_b, stack_a, 1);
	else if (ft_strcmp(instruction, "pb") == 0)
		change_stack(stack_a, stack_b, 1);
	else
		return (0);
	return (1);
}

static void	rotate_stack(t_stack **stack, int reverse)
{
	t_stack	*node;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	if (reverse)
	{
		node = *stack;
		while (node->next->next)
			node = node->next;
		last = node->next;
		node->next = NULL;
		last->next = *stack;
		*stack = last;
	}
	else
	{
		node = *stack;
		*stack = node->next;
		node->next = NULL;
		last = *stack;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}

static int	apply_rotation(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	int	reverse;

	reverse = (ft_strcmp(instruction, "rra") == 0
			|| ft_strcmp(instruction, "rrb") == 0
			|| ft_strcmp(instruction, "rrr") == 0);
	if (ft_strcmp(instruction, "ra") == 0
		|| ft_strcmp(instruction, "rra") == 0)
		rotate_stack(stack_a, reverse);
	else if (ft_strcmp(instruction, "rb") == 0
		|| ft_strcmp(instruction, "rrb") == 0)
		rotate_stack(stack_b, reverse);
	else if (ft_strcmp(instruction, "rr") == 0
		|| ft_strcmp(instruction, "rrr") == 0)
		(rotate_stack(stack_a, reverse), rotate_stack(stack_b, reverse));
	else
		return (0);
	return (1);
}

int	apply_checker_instruction(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (apply_push_swap(instruction, stack_a, stack_b))
		return (1);
	return (apply_rotation(instruction, stack_a, stack_b));
}
