mis sueños rotos

#include "push_swap.h"

void copy_data(char *str, t_stack **stack_a)
{
	t_stack *stack;

	stack = malloc(sizeof(t_stack));
	stack->value = ft_atoi(str);
	stack->next = *stack_a;
	*stack_a = stack
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

	set_stack(argc, argv, &stack_a);
}
;
