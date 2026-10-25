/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:03:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/24 08:05:06 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

t_bench_state	*bench_state(void);

void	bench_reset(void)
{
	t_bench_state	*state;
	int				i;

	state = bench_state();
	i = 0;
	state->total_ops = 0;
	while (i < OP_COUNT)
	{
		state->op_counts[i] = 0;
		i++;
	}
}

void	bench_enable(int enabled)
{
	bench_state()->enabled = enabled;
}

void	bench_record_operation(int operation)
{
	t_bench_state	*state;

	state = bench_state();
	if (!state->enabled || operation < 0 || operation >= OP_COUNT)
		return ;
	state->total_ops++;
	state->op_counts[operation]++;
}

long	bench_get_total_ops(void)
{
	return (bench_state()->total_ops);
}

long	bench_get_op_count(int operation)
{
	if (operation < 0 || operation >= OP_COUNT)
		return (0);
	return (bench_state()->op_counts[operation]);
}
