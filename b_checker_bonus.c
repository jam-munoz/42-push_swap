/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/30 07:47:55 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"

static void	checker_error(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	free(instruction);
	clear_stack(stack_b);
	error_exit(stack_a);
}

static void	reject_flags(int argc, char **argv, t_stack **stack_a)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			error_exit(stack_a);
		i++;
	}
}

static void	check_reverse_instruction(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp("rra", instruction) == 0)
		rra(stack_a);
	else if (ft_strcmp("rrb", instruction) == 0)
		rrb(stack_b);
	else if (ft_strcmp("rrr", instruction) == 0)
		rrr(stack_a, stack_b);
	else
		checker_error(instruction, stack_a, stack_b);
}

static void	check_instructions(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	size_t	len;

	len = ft_strlen(instruction);
	if (len > 0 && instruction[len - 1] == '\n')
		instruction[len - 1] = '\0';
	if (ft_strcmp("sa", instruction) == 0)
		sa(stack_a);
	else if (ft_strcmp("sb", instruction) == 0)
		sb(stack_b);
	else if (ft_strcmp("ss", instruction) == 0)
		ss(stack_a, stack_b);
	else if (ft_strcmp("pa", instruction) == 0)
		pa(stack_a, stack_b);
	else if (ft_strcmp("pb", instruction) == 0)
		pb(stack_a, stack_b);
	else if (ft_strcmp("ra", instruction) == 0)
		ra(stack_a);
	else if (ft_strcmp("rb", instruction) == 0)
		rb(stack_b);
	else if (ft_strcmp("rr", instruction) == 0)
		rr(stack_a, stack_b);
	else
		check_reverse_instruction(instruction, stack_a, stack_b);
}

static int	is_sorted(t_stack *stack_a)
{
	while (stack_a && stack_a->next)
	{
		if (stack_a->number > stack_a->next->number)
			return (0);
		stack_a = stack_a->next;
	}
	return (1);
}

static void	check_stack(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_b == NULL && is_sorted(stack_a))
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	*instruction;
	int		size;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	operation_output_enable(0);
	reject_flags(argc, argv, &stack_a);
	size = parse_args(argc, argv, &stack_a, &(t_run_config){0});
	index_stack(&stack_a, size);
	while (1)
	{
		instruction = get_next_line(STDIN_FILENO);
		if (instruction == NULL)
			break ;
		check_instructions(instruction, &stack_a, &stack_b);
		free(instruction);
	}
	check_stack(stack_a, stack_b);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
