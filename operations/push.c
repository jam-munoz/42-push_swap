#include "operations.h"

static void	push(t_stack **stack_1, t_stack **stack_2)
{
	t_stack	*temp;

	if (!stack_1 || !*stack_1 || !(*stack_1)->next)
		return ;
	temp = (*stack_1)->next;
	(*stack_1)->next = *stack_2;
	*stack_2 = *stack_1;
	*stack_1 = temp;
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_a, stack_b);
	write(STDOUT_FILENO, "pa\n", 3);
}

void	pb(t_stack **stack_b, t_stack **stack_a)
{
	push(stack_b, stack_a);
	write(STDOUT_FILENO, "pb\n", 3);
}
