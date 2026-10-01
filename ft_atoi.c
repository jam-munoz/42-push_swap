/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:11:10 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/01 17:26:34 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	ft_putstr_fd(const char *s, int fd)
{
	const char	*p;

	p = s;
	while (*p != '\0')
		p++;
	write(fd, s, p - s);
}

int	ft_atoi(const char *nptr, t_stack **stack_a)
{
	int	sign;
	int	sum;

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
		{
			ft_putstr_fd("Error.\n", STDERR_FILENO);
			ft_lstclear(stack_a);
			exit(0);
		}
		sum *= 10;
		sum += *nptr - '0';
		nptr++;
	}
	return (sum * sign);
}
