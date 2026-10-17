/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/09 14:51:37 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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

void	adaptive_selection(t_stack **stack_a, t_stack **stack_b)
{
	float	disorder;

	disorder = compute_disorder(*stack_a);
	if (disorder < 0.2)
		insertion_sort(stack_a, stack_b);
	else if (disorder < 0.5)
		chunk_sort(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}

void	algorithm_selector(char *str, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strcmp(str, "--simple") == 0)
		insertion_sort(stack_a, stack_b);
	else if (ft_strcmp(str, "--medium") == 0)
		chunk_sort(stack_a, stack_b);
	else if (ft_strcmp(str, "--complex") == 0)
		radix_sort(stack_a, stack_b);
	else if (ft_strcmp(str, "--adaptive") == 0)
		adaptive_selection(stack_a, stack_b);
	else
		adaptive_selection(stack_a, stack_b);
}

void	check_instructions(char *instruction, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp("sa\n", instruction, 3) == 0)
		sa(stack_a);
	else if (ft_strncmp("sb\n", instruction, 3) == 0)
		sb(stack_b);
	else if (ft_strncmp("ss\n", instruction, 3) == 0)
		ss(stack_a, stack_b);
	else if (ft_strncmp("pa\n", instruction, 3) == 0)
		pa(stack_a, stack_b);
	else if (ft_strncmp("pb\n", instruction, 3) == 0)
		pb(stack_a, stack_b);
	else if (ft_strncmp("ra\n", instruction, 3) == 0)
		ra(stack_a);
	else if (ft_strncmp("rb\n", instruction, 3) == 0)
		rb(stack_b);
	else if (ft_strncmp("rr\n", instruction, 3) == 0)
		rr(stack_a, stack_b);
	else if (ft_strncmp("rra\n", instruction, 4) == 0)
		rra(stack_a);
	else if (ft_strncmp("rrb\n", instruction, 4) == 0)
		rrb(stack_b);
	else if (ft_strncmp("rrr\n", instruction, 4) == 0)
		rrr(stack_a, stack_b);
	else
	{
		clear_stack(stack_b);
		error_exit(stack_a);
	}
}

void	check_stack(t_stack *stack_a)
{
	t_stack *prev;

	while (stack_a->next != NULL)
	{
		prev = stack_a;
		stack_a = stack_a->next;
		if (prev->number > stack_a->number)
		{
			write(STDOUT_FILENO, "KO\n", 3);
			return;
		}
	}
	write(STDOUT_FILENO, "OK\n", 3);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	size = parse_args(argc, argv, &stack_a);
	index_stack(&stack_a, size);
	algorithm_selector(argv[1], &stack_a, &stack_b);
	check_stack(stack_a);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
