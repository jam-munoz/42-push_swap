/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/01 23:12:33 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* valgrind ./push_swap 1 2 3 4 sda tira un bloque sin liberar*/

#include "push_swap.h"

void	print_data(t_stack *stack)
{
	int i;
	t_stack *temp;

	i = 1;
	while (stack != NULL)
	{
		ft_printf("stack %d: %d\n", i, stack->number);
		temp = stack;
		stack = stack->next;
		free(temp);
		i++;
	}
	ft_printf("stack %d: %s\n", i, stack);
}
void	copy_data(char *str, t_stack **stack_a, int *arr)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	if (stack == NULL)
	{
		ft_lstclear(stack_a);
		return ;
	}
	stack->next = *stack_a;
	stack->number = ft_atoi(str, &stack);
	*arr = stack->number;
	*stack_a = stack;
	return ;
}

void	set_stack(int n, char *strs[], t_stack **stack_a)
{
	int	*arr;
	int prueba = n - 1;

	if (n < 2)
		exit(0);
	if (n == 2)
	{
		split_values(strs[1], stack_a, arr);
		return ;
	}
	n--;
	arr = malloc((n) * sizeof(int));
	while (n > 0)
	{
		copy_data(strs[n], stack_a, &arr[n - 1]);
		n--;
	}
	for (int i = 0; i < prueba; i++)
		ft_printf("arr[%d]: %d\n", i, arr[i]);
	free(arr);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	set_stack(argc, argv, &stack_a);
	//rotate(&stack_a);
	//rev_rotate(&stack_a);
	//push(&stack_a, &stack_b);
	//swap(&stack_a);
	ft_printf("--- stack a ---\n");
	print_data(stack_a);
	//ft_printf("--- stack b ---\n");
	//print_data(stack_b);
}
