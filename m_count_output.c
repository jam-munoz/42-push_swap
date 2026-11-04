/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_count_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: divillan <divillan@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 00:00:00 by divillan          #+#    #+#             */
/*   Updated: 2026/11/04 00:00:00 by divillan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

void	print_operation_count(void)
{
	ft_printf(STDOUT_FILENO, "%ld\n", bench_get_total_ops());
}
