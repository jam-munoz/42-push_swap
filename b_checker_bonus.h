/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 17:14:01 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_CHECKER_BONUS_H
# define B_CHECKER_BONUS_H

# include "d_push_swap.h"
# include "ft_get_next_line.h"

int	apply_checker_instruction(char *instruction, t_stack **stack_a,
		t_stack **stack_b);

#endif
