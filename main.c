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

#include "push_swap.h"

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
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
