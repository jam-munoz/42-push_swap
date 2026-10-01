#include "push_swap.h"

void swap(t_stack **stack)
{
	t_stack	*temp;

	temp = *stack->next->next;
	*stack->next->next = *stack;
	*stack->next = temp;
}

void push(t_stack **stack_1, t_stack **stack_2)
{
	t_stack	*temp;

	temp = stack_1->next;
	stack_1->next = *stack_2;
	*stack_2 = *stack_1;
	*stack_1 = temp;
}

void rotate(t_stack **stack)
{
	t_stack	*temp;
	t_stack	rot;

	temp = *stack->next;
	rot = temp;
	while (rot->next != NULL)
		rot = rot->next;
	rot_next = *stack;
	*stack->next = NULL;
	*stack = temp;
}

void rev_rotate(t_stack **stack)
{
	t_stack	*temp;
	t_stack	rot;

	rot = *stack->next;
	while (rot->next->next != NULL)
		rot = rot->next;
	temp = rot->next;
	rot->next = NULL;
	temp->next = *stack;
	*stack = temp;
}

void ss(t_stack **stack_a, t_stack **stack_b)
{
	swap(stack_a);
	swap(stack_b);
}

void rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
}

void rrr(t_stack **stack_a, t_stack **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
}
