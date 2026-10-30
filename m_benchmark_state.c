/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_benchmark_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 17:30:14 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

int	is_bench_flag(char *str)
{
	return (ft_strcmp(str, "--bench") == 0);
}

t_bench_state	*bench_state(void)
{
	static t_bench_state	state;

	return (&state);
}

long	bench_get_op_count(int operation)
{
	if (operation < 0 || operation >= OP_COUNT)
		return (0);
	return (bench_state()->op_counts[operation]);
}
