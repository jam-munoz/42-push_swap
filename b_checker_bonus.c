/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 23:00:00 by divillan          #+#    #+#             */
/*   Updated: 2026/10/30 23:00:00 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"

static void	init_checker(int argc, char **argv, t_stack **stack_a)
{
	t_run_config	config;
	int				i;
	int				size;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			error_exit(stack_a);
		i++;
	}
	size = parse_args(argc, argv, stack_a, &config);
	index_stack(stack_a, size);
}

static void	read_instructions(t_stack **stack_a, t_stack **stack_b)
{
	char	*instruction;
	size_t	len;

	instruction = get_next_line(STDIN_FILENO);
	while (instruction)
	{
		len = ft_strlen(instruction);
		if (len > 0 && instruction[len - 1] == '\n')
			instruction[len - 1] = '\0';
		if (!apply_checker_instruction(instruction, stack_a, stack_b))
		{
			free(instruction);
			clear_stack(stack_b);
			error_exit(stack_a);
		}
		free(instruction);
		instruction = get_next_line(STDIN_FILENO);
	}
}

static void	check_stack(t_stack *stack_a, t_stack *stack_b)
{
	int	sorted;

	sorted = 1;
	while (stack_a && stack_a->next)
	{
		if (stack_a->number > stack_a->next->number)
			sorted = 0;
		stack_a = stack_a->next;
	}
	if (stack_b == NULL && sorted)
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	init_checker(argc, argv, &stack_a);
	read_instructions(&stack_a, &stack_b);
	check_stack(stack_a, stack_b);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
