/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 17:02:25 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/06 15:37:12 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"

static int	parse_int(char **str, t_stack **stack) //es como el atoi
{
	int		sign;
	long	sum;

	sign = 1;
	sum = 0;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	if (**str < '0' || '9' < **str)
		error_exit(stack);
	while ('0' <= **str && **str <= '9')
	{
		sum = sum * 10 + (**str - '0');
		(*str)++;
	}
	sum *= sign;
	if ((**str != '\0' && **str != ' ') || sum < INT_MIN || sum > INT_MAX)
		error_exit(stack);
	return (sum);
}

static void	push_back(t_stack **stack, t_stack **tail, int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (node == NULL)
		error_exit(stack);
	node->number = value;
	node->index = 0;
	node->next = NULL;
	if (*tail == NULL)
		*stack = node;
	else
		(*tail)->next = node;
	*tail = node;
}

static int	parse_str(char *str, t_stack **stack, t_stack **tail)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == ' ')
			str++;
		else
		{
			push_back(stack, tail, parse_int(&str, stack));
			count++;
		}
	}
	return (count);
}

int	parse_args(int argc, char *argv[], t_stack **stack) //un mini-split
{
	t_stack	*tail;
	int		count;
	int		i;

	tail = NULL;
	count = 0;
	i = 2;
	while (i < argc)
	{
		count += parse_str(argv[i], stack, &tail);
		i++;
	}
	if (count == 0)
		error_exit(stack);
	return (count);
}
