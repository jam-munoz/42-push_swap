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

void	adaptive_selection(t_stack **stack_a, t_stack **stack_b, float disorder)
{
	if (disorder < 0.2)
		insertion_sort(stack_a, stack_b);
	else if (disorder < 0.5)
		chunk_sort(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}

void	algorithm_selector(char *str, t_stack **stack_a, t_stack **stack_b, float disorder)
{
	if (ft_strcmp(str, "--simple") == 0)
		insertion_sort(stack_a, stack_b);
	else if (ft_strcmp(str, "--medium") == 0)
		chunk_sort(stack_a, stack_b);
	else if (ft_strcmp(str, "--complex") == 0)
		radix_sort(stack_a, stack_b);
	else if (ft_strcmp(str, "--adaptive") == 0)
		adaptive_selection(stack_a, stack_b, disorder);
	else
		adaptive_selection(stack_a, stack_b, disorder);
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

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size;
	long	inversions;
	float	disorder;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	size = parse_args(argc, argv, &stack_a);
	inversions = index_stack(&stack_a, size);
	if (!is_sorted(stack_a))
	{
		disorder = compute_disorder(inversions, size);
		algorithm_selector(argv[1], &stack_a, &stack_b, disorder);
	}
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
