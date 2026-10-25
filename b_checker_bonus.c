/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:38:57 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"

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

void	check_stack(t_stack *stack_a)
{
	t_stack	*prev;

	while (stack_a->next != NULL)
	{
		prev = stack_a;
		stack_a = stack_a->next;
		if (prev->number > stack_a->number)
		{
			write(STDOUT_FILENO, "KO\n", 3);
			return ;
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
	size = parse_args(argc, argv, &stack_a, &(t_run_config){0});
	index_stack(&stack_a, size);
	algorithm_selector(argv[1], &stack_a, &stack_b);
	check_stack(stack_a);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
