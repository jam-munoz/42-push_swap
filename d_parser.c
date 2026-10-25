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
#include "d_push_swap.h"

static int	parse_int(char **str, t_stack **stack)
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

static void	parse_argument(char *arg, t_parse_context *context)
{
	if (!context->numbers_found && is_mode_flag(arg))
	{
		if (context->mode_found)
			error_exit(context->stack);
		context->config->mode = arg;
		context->mode_found = 1;
	}
	else if (!context->numbers_found && is_bench_flag(arg))
	{
		if (context->config->bench)
			error_exit(context->stack);
		context->config->bench = 1;
	}
	else
	{
		if (arg[0] == '-' && arg[1] == '-')
			error_exit(context->stack);
		context->numbers_found = 1;
		context->count += parse_str(arg, context->stack, context->tail);
	}
}

int	parse_args(int argc, char *argv[], t_stack **stack, t_run_config *config)
{
	t_stack			*tail;
	t_parse_context	context;
	int				i;

	tail = NULL;
	context.stack = stack;
	context.tail = &tail;
	context.config = config;
	context.numbers_found = 0;
	context.mode_found = 0;
	context.count = 0;
	i = 1;
	config->mode = "--adaptive";
	config->bench = 0;
	while (i < argc)
	{
		parse_argument(argv[i], &context);
		i++;
	}
	if (context.count == 0)
		error_exit(stack);
	return (context.count);
}
