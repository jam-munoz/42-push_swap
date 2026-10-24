/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/24 08:57:34 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_strategy_info	make_strategy(const char *name, const char *complexity)
{
	t_strategy_info	strategy;

	strategy.name = name;
	strategy.complexity = complexity;
	return (strategy);
}

static t_strategy_info	select_adaptive(t_stack **stack_a, t_stack **stack_b,
		float disorder)
{
	int	n;

	n = get_stack_size(*stack_a);
	if (n == 2)
		return (two_sort(stack_a), make_strategy("Adaptive", "O(1)"));
	if (n == 3)
		return (three_sort(stack_a, 0), make_strategy("Adaptive", "O(1)"));
	if (n == 4)
		return (four_sort(stack_a, stack_b),
			make_strategy("Adaptive", "O(1)"));
	if (n == 5)
		return (five_sort(stack_a, stack_b),
			make_strategy("Adaptive", "O(1)"));
	if (disorder < 0.2)
		return (insertion_sort(stack_a, stack_b),
			make_strategy("Adaptive", "O(n^2)"));
	if (disorder < 0.5)
		return (chunk_sort(stack_a, stack_b),
			make_strategy("Adaptive", "O(n\u221a2)"));
	radix_sort(stack_a, stack_b);
	return (make_strategy("Adaptive", "O(n log n)"));
}

void	select_strategy(t_request *request)
{
	if (ft_strcmp(request->mode, "--simple") == 0)
		*request->strategy = (insertion_sort(request->stack_a,
					request->stack_b),
				make_strategy("Simple", "O(n^2)"));
	else if (ft_strcmp(request->mode, "--medium") == 0)
		*request->strategy = (chunk_sort(request->stack_a,
					request->stack_b),
				make_strategy("Medium", "O(n\u221a2)"));
	else if (ft_strcmp(request->mode, "--complex") == 0)
		*request->strategy = (radix_sort(request->stack_a,
					request->stack_b),
				make_strategy("Complex", "O(n log n)"));
	else
		*request->strategy = select_adaptive(request->stack_a,
				request->stack_b, request->disorder);
}
