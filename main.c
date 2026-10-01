
#include "push_swap.h"

void print_data(t_stack *stack)
{
	int i;

	i = 1;
	while (stack != NULL)
	{
		ft_printf("stack %d: %d\n", i, stack->number);
		stack = stack->next;
		i++;
	}
	ft_printf("stack %d: %s\n", i, stack);
}
void copy_data(char *str, t_stack **stack_a)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	if (stack == NULL)
	{
		ft_lstclear(stack_a);
		return ;
	}
	stack->number = ft_atoi(str, stack_a);
	stack->next = *stack_a;
	*stack_a = stack;
	return ;
}

void set_stack(int n, char *strs[], t_stack **stack_a)
{
	int i;

	i = 1;
	if (n < 2)
		exit(0);
	if (n == 2)
	{
		split_values(strs[1], stack_a);
		return ;
	}

	while (i < n)
	{
		copy_data(strs[i], stack_a);
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	set_stack(argc, argv, &stack_a);
	print_data(stack_a);
}
