/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_count.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 00:00:00 by divillan          #+#    #+#             */
/*   Updated: 2026/11/04 00:00:00 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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

static float	compute_disorder(long inversions, int size)
{
	long	max_inversions;

	max_inversions = (long)size * (size - 1) / 2;
	if (max_inversions == 0)
		return (0.0f);
	return ((float)inversions / max_inversions);
}

static void	run_sort_silently(t_stack **stack_a, t_stack **stack_b,
		t_run_config *config, int size)
{
	long			inversions;
	float			disorder;
	t_strategy_info	strategy;
	t_request		request;

	bench_reset();
	bench_enable(1);
	inversions = index_stack(stack_a, size);
	disorder = compute_disorder(inversions, size);
	if (!is_sorted(*stack_a))
	{
		strategy.name = "count";
		strategy.complexity = "count";
		request.mode = config->mode;
		request.stack_a = stack_a;
		request.stack_b = stack_b;
		request.disorder = disorder;
		request.strategy = &strategy;
		select_strategy(&request);
	}
}

static int	remove_count_flag(int argc, char **argv, char **clean_argv)
{
	int	i;
	int	clean_argc;
	int	found;

	i = 0;
	clean_argc = 0;
	found = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--count") == 0)
		{
			if (found)
				return (-1);
			found = 1;
		}
		else
			clean_argv[clean_argc++] = argv[i];
		i++;
	}
	clean_argv[clean_argc] = NULL;
	if (!found)
		return (-1);
	return (clean_argc);
}

static int	silence_stdout(int *saved_stdout)
{
	int	null_fd;

	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout < 0)
		return (-1);
	null_fd = open("/dev/null", O_WRONLY);
	if (null_fd < 0)
	{
		close(*saved_stdout);
		return (-1);
	}
	if (dup2(null_fd, STDOUT_FILENO) < 0)
	{
		close(null_fd);
		close(*saved_stdout);
		return (-1);
	}
	close(null_fd);
	return (0);
}

int	main(int argc, char **argv)
{
	char		*clean_argv[argc + 1];
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_run_config	config;
	int			clean_argc;
	int			saved_stdout;
	int			size;

	clean_argc = remove_count_flag(argc, argv, clean_argv);
	if (clean_argc < 2)
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	stack_a = NULL;
	stack_b = NULL;
	size = parse_args(clean_argc, clean_argv, &stack_a, &config);
	if (silence_stdout(&saved_stdout) < 0)
	{
		clear_stack(&stack_a);
		clear_stack(&stack_b);
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	run_sort_silently(&stack_a, &stack_b, &config, size);
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
	{
		close(saved_stdout);
		clear_stack(&stack_a);
		clear_stack(&stack_b);
		write(STDERR_FILENO, "Error\n", 6);
		return (1);
	}
	close(saved_stdout);
	ft_printf(STDOUT_FILENO, "%ld\n", bench_get_total_ops());
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
