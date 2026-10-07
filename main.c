/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/07 14:32:59 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_data(t_stack *stack)
{
	int		i;
	/*t_stack	*temp;*/

	i = 1;
	while (stack != NULL)
	{
		ft_printf("stack %d:\t|-|\tnumber: %d\t|-|\tindex: %d\n", i, stack->number, stack->index);
		/*temp = stack;*/
		stack = stack->next;
		i++;
	}
	ft_printf("stack %d: %s\n", i, stack);
}

void	algorithm_selector(char *argv[], t_stack *stack_a, t_stack *stack_b)
{
	if (ft_strcmp(argv[1], "--simple") == 0)
		insertion_sort(&stack_a, &stack_b);
	if (ft_strcmp(argv[1], "--medium") == 0)
		chunk_sort(&stack_a, &stack_b);
	if (ft_strcmp(argv[1], "--complex") == 0)
		radix_sort(&stack_a, &stack_b);
	/*if (argv[1] == '--adaptative')*/
	else
		error_exit(&stack_a);
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
	print_data(stack_a);
	algorithm_selector(argv, stack_a, stack_b);
	print_data(stack_a);
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
