/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:12:37 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/18 18:26:34 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "./ft_printf/ft_printf.h"
# include "./operations/operations.h"

typedef struct s_run_config
{
	char	*mode;
	int		bench;
}	t_run_config;

typedef struct s_strategy_info
{
	const char	*name;
	const char	*complexity;
}	t_strategy_info;

typedef enum e_operation
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_operation;

void	copy_data(char *str, t_stack **stack_a, int *arr, int *p);
int		parse_args(int argc, char *argv[], t_stack **stack, t_run_config *config);
long	index_stack(t_stack **stack, int size);
int		get_stack_size(t_stack *stack);
int		ft_sqrt(int nb);
void	clear_stack(t_stack **stack);
void	error_exit(t_stack **stack);
int		ft_strcmp(const char *s1, const char *s2);
float	compute_disorder(long inversions, int size);
void	two_sort(t_stack **stack_a);
void	three_sort(t_stack **stack_a, int i);
void	four_sort(t_stack **stack_a, t_stack **stack_b);
void	five_sort(t_stack **stack_a, t_stack **stack_b);
void	insertion_sort(t_stack **stack_a, t_stack **stack_b);
void	chunk_sort(t_stack **stack_a, t_stack **stack_b);
void	radix_sort(t_stack **stack_a, t_stack **stack_b);
void	bench_reset(void);
void	bench_enable(int enabled);
void	bench_record_operation(int operation);
long	bench_get_total_ops(void);
long	bench_get_op_count(int operation);

#endif
