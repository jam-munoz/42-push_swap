/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 06:20:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/24 08:43:22 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_buf_putc(t_printf *pf, char c)
{
	if (pf->buf_len == BUF_SIZE)
		ft_print_buf(pf);
	pf->buf[pf->buf_len++] = c;
}

static void	ft_put_ul(t_printf *pf, unsigned long n)
{
	char	digits[20];
	int		i;

	if (n == 0)
	{
		ft_buf_putc(pf, '0');
		return ;
	}
	i = 0;
	while (n > 0)
	{
		digits[i++] = (char)((n % 10) + '0');
		n /= 10;
	}
	while (i > 0)
		ft_buf_putc(pf, digits[--i]);
}

void	ft_print_float(t_printf *pf)
{
	double			n;
	long			scaled;
	unsigned long	abs_scaled;
	unsigned int	decimals;

	n = va_arg(pf->ap, double);
	if (n >= 0.0)
		scaled = (long)(n * 100.0 + 0.5);
	else
		scaled = (long)(n * 100.0 - 0.5);
	if (scaled < 0)
	{
		ft_buf_putc(pf, '-');
		abs_scaled = (unsigned long)(-scaled);
	}
	else
		abs_scaled = (unsigned long)scaled;
	ft_put_ul(pf, abs_scaled / 100);
	decimals = (unsigned int)(abs_scaled % 100);
	ft_buf_putc(pf, '.');
	ft_buf_putc(pf, (char)((decimals / 10) + '0'));
	ft_buf_putc(pf, (char)((decimals % 10) + '0'));
}
