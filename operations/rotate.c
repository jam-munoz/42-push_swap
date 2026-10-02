#include "operations.h"

static void	rotate(t_stack **stack)
{
	t_stack	*temp;
	t_stack	*rot;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	temp = (*stack)->next;
	rot = temp;
	while (rot->next != NULL)
		rot = rot->next;
	rot->next = *stack;
	(*stack)->next = NULL;
	*stack = temp;
}

void	ra(t_stack **stack_a)
{
	rotate(stack_a);
	write(STDOUT_FILENO, "ra\n", 3);
}

void	rb(t_stack **stack_b)
{
	rotate(stack_b);
	write(STDOUT_FILENO, "rb\n", 3);
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	write(STDOUT_FILENO, "rr\n", 3);
}
