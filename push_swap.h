/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:37 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/06 15:50:07 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "./ft_printf/ft_printf.h"
# include "./operations/operations.h"

void	copy_data(char *str, t_stack **stack_a, int *arr, int *p);
int		parse_args(int argc, char *argv[], t_stack **stack);
void	index_stack(t_stack **stack, int size);
int		get_stack_size(t_stack *stack);
void	clear_stack(t_stack **stack);
void	error_exit(t_stack **stack);

int		ft_strcmp(const char *s1, const char *s2);

void	insertion_sort(t_stack **stack_a, t_stack **stack_b);
void	chunk_sort(t_stack **stack_a, t_stack **stack_b);
void	radix_sort(t_stack **stack_a, t_stack **stack_b);

#endif
