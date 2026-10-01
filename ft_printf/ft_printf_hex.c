/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 11:23:53 by joamunoz          #+#    #+#             */
/*   Updated: 2026/09/02 12:43:58 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_zero(unsigned long n, t_printf *pf);

static int	ft_hex_digit_count(unsigned long n)
{
	int	digits;

	digits = 0;
	while (n > 0)
	{
		n >>= 4;
		digits++;
	}
	return (digits);
}

void	ft_print_hex(t_printf *pf)
{
	unsigned int	n;
	int				digits;
	const char		*hex_digits;

	n = va_arg(pf->ap, unsigned int);
	if (ft_print_zero(n, pf))
		return ;
	if (*pf->format == 'X')
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	digits = ft_hex_digit_count(n);
	if (pf->buf_len + digits > BUF_SIZE)
		ft_print_buf(pf);
	pf->buf_len += digits;
	pf->count += digits;
	digits = pf->buf_len;
	while (n > 0)
	{
		pf->buf[--digits] = hex_digits[n & 0xF];
		n >>= 4;
	}
}

void	ft_print_ptr(t_printf *pf)
{
	unsigned long	n;
	int				digits;
	const char		*hex_digits;

	n = (unsigned long)va_arg(pf->ap, void *);
	if (ft_print_zero(n, pf))
		return ;
	hex_digits = "0123456789abcdef";
	digits = ft_hex_digit_count(n) + 2;
	if (pf->buf_len + digits > BUF_SIZE)
		ft_print_buf(pf);
	pf->buf[pf->buf_len] = '0';
	pf->buf[pf->buf_len + 1] = 'x';
	pf->buf_len += digits;
	pf->count += digits;
	digits = pf->buf_len;
	while (n > 0)
	{
		pf->buf[--digits] = hex_digits[n & 0xF];
		n >>= 4;
	}
}
