/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/02 18:54:01 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_data(t_stack *stack)
{
	int		i;
	t_stack	*temp;

	i = 1;
	while (stack != NULL)
	{
		ft_printf("stack %d:\t|-|\tnumber: %d\t|-|\tindex: %d\n", i, stack->number, stack->index);
		temp = stack;
		stack = stack->next;
		i++;
	}
	ft_printf("stack %d: %s\n", i, stack);
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
	/* sorting goes here */
	clear_stack(&stack_a);
	clear_stack(&stack_b);
	return (0);
}
