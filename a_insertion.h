/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_insertion.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_INSERTION_H
# define A_INSERTION_H

# include "d_push_swap.h"

typedef struct s_insertion_move
{
	int	a_rotations;
	int	b_rotations;
	int	total;
	int	found;
}	t_insertion_move;

t_insertion_move	find_best_insertion(t_stack *stack_a, t_stack *stack_b);
void				apply_insertion_rotations(t_stack **stack_a,
						t_stack **stack_b, t_insertion_move move);

#endif
