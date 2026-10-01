/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:11:10 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/01 23:20:51 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"

void	error_exit(t_stack **stack)
{
	ft_lstclear(stack);
	write(STDERR_FILENO ,"Error.\n", 7);
	exit(0);
}
void	ft_lstclear(t_stack **lst)
{
	t_stack	*p;
	t_stack	*remove;

	if (lst == NULL)
		return ;
	p = *lst;
	while (p != NULL)
	{
		remove = p;
		p = p->next;
		free(remove);
	}
	*lst = NULL;
}

int	ft_atoi(const char *nptr, t_stack **stack)
{
	int		sign;
	long	sum;

	sign = 1;
	sum = 0;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && *nptr != ' ')
	{
		if (*nptr < '0' || '9' < *nptr)
			error_exit(stack);
		sum *= 10;
		sum += *nptr - '0';
		nptr++;
	}
	sum *= sign;
	if (sum < INT_MIN || sum > INT_MAX)
		error_exit(stack);
	return (sum);
}
