#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include "./ft_printf/ft_printf.h"

typedef struct s_stack
{
	int	number;
	int	index;
	struct s_stack *next;
}	t_stack;

void copy_data(char *str, t_stack **stack_a);
void	ft_putstr_fd(const char *s, int fd);
void	ft_lstclear(t_stack **lst);
int	ft_atoi(const char *nptr, t_stack **stack_a);
void split_values(char *str, t_stack **stack_a);
void swap(t_stack **stack);
void push(t_stack **stack_1, t_stack **stack_2);
void rotate(t_stack **stack);
void rev_rotate(t_stack **stack);
void ss(t_stack **stack_a, t_stack **stack_b);
void rr(t_stack **stack_a, t_stack **stack_b);
void rrr(t_stack **stack_a, t_stack **stack_b);

#endif
