/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:37 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/02 09:09:27 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	copy_data(char *str, t_stack **stack_a, int *arr, int *p);
void	error_exit(t_stack **stack, int *arr);
void	ft_lstclear(t_stack **lst);
int		ft_atoi(const char *nptr, t_stack **stack_a, int *arr);
int		split_values(char *str, t_stack **stack_a, int **arr);
void	swap(t_stack **stack);
void	push(t_stack **stack_1, t_stack **stack_2);
void	rotate(t_stack **stack);
void	rev_rotate(t_stack **stack);
void	ss(t_stack **stack_a, t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);

#endif
