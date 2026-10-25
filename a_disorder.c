/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 20:33:58 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/13 20:34:04 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "d_push_swap.h"

float	compute_disorder(long inversions, int size)
{
	long	max_inversions;

	max_inversions = (long)size * (size - 1) / 2;
	if (max_inversions == 0)
		return (0.0f);
	return ((float)inversions / max_inversions);
}
