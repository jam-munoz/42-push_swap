/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:03:00 by divillan          #+#    #+#             */
/*   Updated: 2026/10/23 19:03:00 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	g_bench_enabled = 0;
static long	g_total_ops = 0;
static long	g_op_counts[OP_COUNT];

void	bench_reset(void)
{
	int	i;

	i = 0;
	g_total_ops = 0;
	while (i < OP_COUNT)
	{
		g_op_counts[i] = 0;
		i++;
	}
}

void	bench_enable(int enabled)
{
	g_bench_enabled = enabled;
}

void	bench_record_operation(int operation)
{
	if (!g_bench_enabled || operation < 0 || operation >= OP_COUNT)
		return ;
	g_total_ops++;
	g_op_counts[operation]++;
}

long	bench_get_total_ops(void)
{
	return (g_total_ops);
}

long	bench_get_op_count(int operation)
{
	if (operation < 0 || operation >= OP_COUNT)
		return (0);
	return (g_op_counts[operation]);
}
