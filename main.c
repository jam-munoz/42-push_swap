/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/18 18:26:42 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	print_data(t_stack *stack)
{
	int	i;

	i = 1;
	while (stack != NULL)
	{
		ft_printf("stack %d:\t|-|\tnumber: %d\t|-|\tindex:%d\n",
			i, stack->number, stack->index);
		stack = stack->next;
		i++;
	}
	ft_printf("stack %d: %s\n", i, stack);
}

static const t_strategy_info	*g_two = &(t_strategy_info){"two_sort", "O(1)"};
static const t_strategy_info	*g_three = &(t_strategy_info){"three_sort", "O(1)"};
static const t_strategy_info	*g_four = &(t_strategy_info){"four_sort", "O(1)"};
static const t_strategy_info	*g_five = &(t_strategy_info){"five_sort", "O(1)"};
static const t_strategy_info	*g_insertion = &(t_strategy_info){"insertion_sort", "O(n^2)"};
static const t_strategy_info	*g_chunk = &(t_strategy_info){"chunk_sort", "O(n^2)"};
static const t_strategy_info	*g_radix = &(t_strategy_info){"radix_sort", "O(n log n)"};
static const t_strategy_info	*g_noop = &(t_strategy_info){"no_sort (already sorted)", "O(1)"};

static const t_strategy_info	*adaptive_selection(t_stack **stack_a,
		t_stack **stack_b, float disorder)
{
	int	n;

	n = get_stack_size(*stack_a);
	if (n == 2)
	{
		two_sort(stack_a);
		return (g_two);
	}
	else if (n == 3)
	{
		three_sort(stack_a, 0);
		return (g_three);
	}
	else if (n == 4)
	{
		four_sort(stack_a, stack_b);
		return (g_four);
	}
	else if (n == 5)
	{
		five_sort(stack_a, stack_b);
		return (g_five);
	}
	else if (disorder < 0.2)
	{
		insertion_sort(stack_a, stack_b);
		return (g_insertion);
	}
	else if (disorder < 0.5)
	{
		chunk_sort(stack_a, stack_b);
		return (g_chunk);
	}
	else
	{
		radix_sort(stack_a, stack_b);
		return (g_radix);
	}
}

const t_strategy_info	*algorithm_selector(char *str, t_stack **stack_a,
		t_stack **stack_b, float disorder)
{
	if (ft_strcmp(str, "--simple") == 0)
	{
		insertion_sort(stack_a, stack_b);
		return (g_insertion);
	}
	else if (ft_strcmp(str, "--medium") == 0)
	{
		chunk_sort(stack_a, stack_b);
		return (g_chunk);
	}
	else if (ft_strcmp(str, "--complex") == 0)
	{
		radix_sort(stack_a, stack_b);
		return (g_radix);
	}
	else if (ft_strcmp(str, "--adaptive") == 0)
		return (adaptive_selection(stack_a, stack_b, disorder));
	return (adaptive_selection(stack_a, stack_b, disorder));
}

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->index > stack->next->index)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	print_benchmark(float disorder, const t_strategy_info *strategy)
{
	static const char	*op_names[OP_COUNT] = {"sa", "sb", "ss", "pa", "pb",
		"ra", "rb", "rr", "rra", "rrb", "rrr"};
	int					i;

	dprintf(STDERR_FILENO, "Disorder: %.2f%%\n", disorder * 100.0f);
	dprintf(STDERR_FILENO, "Strategy: %s (%s)\n", strategy->name,
		strategy->complexity);
	dprintf(STDERR_FILENO, "Total operations: %ld\n", bench_get_total_ops());
	i = 0;
	while (i < OP_COUNT)
	{
		dprintf(STDERR_FILENO, "%s: %ld\n", op_names[i], bench_get_op_count(i));
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_run_config	config;
	const t_strategy_info	*strategy;
	int		size;
	long	inversions;
	float	disorder;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	bench_reset();
	size = parse_args(argc, argv, &stack_a, &config);
	bench_enable(config.bench);
	inversions = index_stack(&stack_a, size);
	disorder = compute_disorder(inversions, size);
	strategy = g_noop;
	if (!is_sorted(stack_a))
	{
		strategy = algorithm_selector(config.mode, &stack_a, &stack_b, disorder);
	}
	if (config.bench)
		print_benchmark(disorder, strategy);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
