/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/02 09:09:03 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* valgrind ./push_swap 1 2 3 4 sda tira un bloque sin liberar*/

#include "push_swap.h"

int comp(const void* a,const void* b)
{
	return *(int*)a - *(int*)b;
}

void	print_data(t_stack *stack)
{
	int i;
	t_stack *temp;

	i = 1;
	while (stack != NULL)
	{
		ft_printf("stack %d number: %d --- index: %d\n", i, stack->number, stack->index);
		temp = stack;
		stack = stack->next;
		free(temp);
		i++;
	}
	ft_printf("stack %d: %s\n", i, stack);
}
void	copy_data(char *str, t_stack **stack_a, int *arr, int *p)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	if (stack == NULL)
	{
		ft_lstclear(stack_a);
		return ;
	}
	stack->next = *stack_a;
	stack->number = ft_atoi(str, &stack, p);
	*arr = stack->number;
	*stack_a = stack;
	return ;
}

void	parse_index(t_stack **stack, int *arr, int size)
{
	int		i;
	t_stack	*p;

	i = 0;
	while (i < size - 1)
	{
		p = *stack;
		if (arr[i] == arr[i + 1])
			error_exit(stack, arr);
		while (p->number != arr[i])
			p = p->next;
		p->index = i;
		i++;
	}
	p = *stack;
	while (p->number != arr[i])
		p = p->next;
	p->index = i;
}

void	set_stack(int n, char *strs[], t_stack **stack)
{
	int	*arr;
	int prueba = n - 1;

	if (n < 2)
		exit(0);
	if (n == 2)
		prueba = split_values(strs[1], stack, &arr);
	else
	{
		n--;
		arr = malloc((n) * sizeof(int));
		while (n > 0)
		{
			copy_data(strs[n], stack, &arr[n - 1], arr);
			n--;
		}
	}
	qsort(arr, prueba, sizeof(int), comp); //reemplazar por un sort propio. y arreglar el de si n == 2 (que tira segfault)
	parse_index(stack, arr, prueba);
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
