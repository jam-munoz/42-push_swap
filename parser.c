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

static int	is_mode_flag(char *str)
{
	if (ft_strcmp(str, "--simple") == 0)
		return (1);
	else if (ft_strcmp(str, "--medium") == 0)
		return (1);
	else if (ft_strcmp(str, "--complex") == 0)
		return (1);
	else if (ft_strcmp(str, "--adaptive") == 0)
		return (1);
	else
		return (0);
}

static int	is_bench_flag(char *str)
{
	return (ft_strcmp(str, "--bench") == 0);
}

int	parse_args(int argc, char *argv[], t_stack **stack, t_run_config *config)
{
	t_stack	*tail;
	int		count;
	int		i;
	int		numbers_found;
	int		mode_found;

	tail = NULL;
	count = 0;
	i = 1;
	numbers_found = 0;
	mode_found = 0;
	config->mode = "--adaptive";
	config->bench = 0;
	while (i < argc)
	{
		if (!numbers_found && is_mode_flag(argv[i]))
		{
			if (mode_found)
				error_exit(stack);
			config->mode = argv[i];
			mode_found = 1;
		}
		else if (!numbers_found && is_bench_flag(argv[i]))
		{
			if (config->bench)
				error_exit(stack);
			config->bench = 1;
		}
		else
		{
			if (argv[i][0] == '-' && argv[i][1] == '-')
				error_exit(stack);
			numbers_found = 1;
			count += parse_str(argv[i], stack, &tail);
		}
		i++;
	}
	if (count == 0)
		error_exit(stack);
	return (count);
}
