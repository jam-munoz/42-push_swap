/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 08:00:06 by joamunoz         ###   ########.fr       */
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

void	check_reverse_instruction(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp("rra\n", instruction) == 0)
		rra(stack_a);
	else if (ft_strcmp("rrb\n", instruction) == 0)
		rrb(stack_b);
	else if (ft_strcmp("rrr\n", instruction) == 0)
		rrr(stack_a, stack_b);
	else
		checker_error(instruction, stack_a, stack_b);
}

void	check_instructions(char *instruction, t_stack **stack_a,
		t_stack **stack_b)
{
	if (ft_strcmp("sa\n", instruction) == 0)
		sa(stack_a);
	else if (ft_strcmp("sb\n", instruction) == 0)
		sb(stack_b);
	else if (ft_strcmp("ss\n", instruction) == 0)
		ss(stack_a, stack_b);
	else if (ft_strcmp("pa\n", instruction) == 0)
		pa(stack_a, stack_b);
	else if (ft_strcmp("pb\n", instruction) == 0)
		pb(stack_a, stack_b);
	else if (ft_strcmp("ra\n", instruction) == 0)
		ra(stack_a);
	else if (ft_strcmp("rb\n", instruction) == 0)
		rb(stack_b);
	else if (ft_strcmp("rr\n", instruction) == 0)
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

void	check_stack(t_stack *stack_a, t_stack *stack_b)
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
	reject_flags(argc, argv, &stack_a);
	size = parse_args(argc, argv, &stack_a, &(t_run_config){0});
	index_stack(&stack_a, size);
	set_operation_output(0);
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
