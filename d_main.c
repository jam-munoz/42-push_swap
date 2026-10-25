/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:09:47 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

static int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->index > stack->next->index)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	print_benchmark(float disorder, t_strategy_info strategy)
{
	static const char	*op_names[OP_COUNT] = {"sa", "sb", "ss", "pa", "pb",
		"ra", "rb", "rr", "rra", "rrb", "rrr"};
	int					i;

	ft_printf(STDERR_FILENO, "[bench] disorder: %f%%\n", disorder * 100.0f);
	ft_printf(STDERR_FILENO, "[bench] strategy: %s / (%s)\n", strategy.name,
		strategy.complexity);
	ft_printf(STDERR_FILENO, "[bench] total_ops: %d\n", bench_get_total_ops());
	i = 0;
	ft_printf(STDERR_FILENO, "[bench] ");
	while (i < OP_COUNT / 2)
	{
		ft_printf(2, "%s: %d\t", op_names[i], bench_get_op_count(i));
		i++;
	}
	ft_printf(STDERR_FILENO, "\n[bench] ");
	while (i < OP_COUNT)
	{
		ft_printf(2, "%s: %d\t", op_names[i], bench_get_op_count(i));
		i++;
	}
	ft_printf(STDERR_FILENO, "\n");
}

static void	run_sort(t_stack **stack_a, t_stack **stack_b,
		t_run_config *config, int size)
{
	long			inversions;
	float			disorder;
	t_strategy_info	strategy;
	t_request		request;

	bench_reset();
	bench_enable(config->bench);
	inversions = index_stack(stack_a, size);
	disorder = compute_disorder(inversions, size);
	strategy.name = "no_sort (already sorted)";
	strategy.complexity = "O(1)";
	if (!is_sorted(*stack_a))
	{
		request.mode = config->mode;
		request.stack_a = stack_a;
		request.stack_b = stack_b;
		request.disorder = disorder;
		request.strategy = &strategy;
		select_strategy(&request);
	}
	if (config->bench)
		print_benchmark(disorder, strategy);
}

int	main(int argc, char *argv[])
{
	t_stack			*stack_a;
	t_stack			*stack_b;
	t_run_config	config;
	int				size;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	size = parse_args(argc, argv, &stack_a, &config);
	run_sort(&stack_a, &stack_b, &config, size);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
