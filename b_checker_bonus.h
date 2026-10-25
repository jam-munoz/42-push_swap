/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 07:56:50 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_CHECKER_BONUS_H
# define B_CHECKER_BONUS_H

# include "d_push_swap.h"

void	check_instructions(char *instruction, t_stack **stack_a,
			t_stack **stack_b);
void	check_reverse_instruction(char *instruction, t_stack **stack_a,
			t_stack **stack_b);
void	check_stack(t_stack *stack_a);
void	adaptive_selection(t_stack **stack_a, t_stack **stack_b);
void	algorithm_selector(char *str, t_stack **stack_a, t_stack **stack_b);

#endif
