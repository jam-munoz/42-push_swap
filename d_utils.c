/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:37 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/06 21:40:34 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

static int	g_operation_output = 1;

void	set_operation_output(int enabled)
{
	g_operation_output = enabled;
}

int	operation_output_enabled(void)
{
	return (g_operation_output);
}

void	clear_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*next;

	if (stack == NULL)
		return ;
	current = *stack;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}

void	error_exit(t_stack **stack)
{
	clear_stack(stack);
	write(STDERR_FILENO, "Error\n", 6);
	exit(1);
}

int	get_stack_size(t_stack *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_sqrt(int nb)
{
	long	x;
	long	y;

	if (nb < 1)
		return (0);
	x = nb;
	y = (x + 1) / 2;
	while (y < x)
	{
		x = y;
		y = (x + nb / x) / 2;
	}
	return ((int)x);
}
