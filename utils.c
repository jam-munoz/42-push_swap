#include "push_swap.h"

void	clear_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*next;

	if (stack == NULL)
		return ;
	current = *stack;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}

void	error_exit(t_stack **stack)
{
	clear_stack(stack);
	write(STDERR_FILENO, "Error\n", 6);
	exit(1);
}
