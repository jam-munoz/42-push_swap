/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 09:35:48 by joamunoz          #+#    #+#             */
/*   Updated: 2026/09/02 12:43:51 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_digit_count(unsigned int n)
{
	if (n < 10)
		return (1);
	if (n < 100)
		return (2);
	if (n < 1000)
		return (3);
	if (n < 10000)
		return (4);
	if (n < 100000)
		return (5);
	if (n < 1000000)
		return (6);
	if (n < 10000000)
		return (7);
	if (n < 100000000)
		return (8);
	if (n < 1000000000)
		return (9);
	return (10);
}

int	ft_print_zero(unsigned long n, t_printf *pf)
{
	if (n == 0)
	{
		if (*pf->format != 'p')
		{
			pf->buf[pf->buf_len++] = '0';
			pf->count++;
		}
		else
		{
			if (pf->buf_len + 5 > BUF_SIZE)
				ft_print_buf(pf);
			pf->buf[pf->buf_len++] = '(';
			pf->buf[pf->buf_len++] = 'n';
			pf->buf[pf->buf_len++] = 'i';
			pf->buf[pf->buf_len++] = 'l';
			pf->buf[pf->buf_len++] = ')';
			pf->count += 5;
		}
		return (1);
	}
	return (0);
}

void	ft_print_int(t_printf *pf)
{
	long	n;
	int		digits;

	n = va_arg(pf->ap, int);
	if (ft_print_zero(n, pf))
		return ;
	if (n < 0)
	{
		n = -n;
		pf->buf[pf->buf_len++] = '-';
		pf->count++;
	}
	digits = ft_digit_count(n);
	if (pf->buf_len + digits > BUF_SIZE)
		ft_print_buf(pf);
	pf->buf_len += digits;
	pf->count += digits;
	digits = pf->buf_len;
	while (n > 0)
	{
		pf->buf[--digits] = (n % 10) + '0';
		n /= 10;
	}
}

void	ft_print_uint(t_printf *pf)
{
	unsigned int	n;
	int				digits;

	n = va_arg(pf->ap, unsigned int);
	if (ft_print_zero(n, pf))
		return ;
	digits = ft_digit_count(n);
	if (pf->buf_len + digits > BUF_SIZE)
		ft_print_buf(pf);
	pf->buf_len += digits;
	pf->count += digits;
	digits = pf->buf_len;
	while (n > 0)
	{
		pf->buf[--digits] = (n % 10) + '0';
		n /= 10;
	}
}
