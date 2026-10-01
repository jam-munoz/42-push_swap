/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:48:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/09/09 19:36:21 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	ft_print_buf(t_printf *pf)
{
	write(STDOUT_FILENO, pf->buf, pf->buf_len);
	pf->buf_len = 0;
}

static void	ft_print_str(t_printf *pf)
{
	char	*str;

	str = va_arg(pf->ap, char *);
	if (str == (void *)0)
		str = "(null)";
	while (*str != '\0')
	{
		pf->buf[pf->buf_len++] = *str;
		if (pf->buf_len == BUF_SIZE)
			ft_print_buf(pf);
		pf->count++;
		str++;
	}
}

static void	ft_conversion(t_printf *pf)
{
	pf->format++;
	if (*pf->format == 'd' || *pf->format == 'i')
		ft_print_int(pf);
	else if (*pf->format == 's')
		ft_print_str(pf);
	else if (*pf->format == 'c')
	{
		pf->buf[pf->buf_len++] = (char)va_arg(pf->ap, int);
		pf->count++;
	}
	else if (*pf->format == 'u')
		ft_print_uint(pf);
	else if (*pf->format == 'x' || *pf->format == 'X')
		ft_print_hex(pf);
	else if (*pf->format == '%')
	{
		pf->buf[pf->buf_len++] = '%';
		pf->count++;
	}
	else if (*pf->format == 'p')
		ft_print_ptr(pf);
}

int	ft_printf(const char *format, ...)
{
	t_printf	pf;

	pf.format = format;
	pf.buf_len = 0;
	pf.count = 0;
	va_start(pf.ap, format);
	while (*pf.format != '\0')
	{
		if (*pf.format == '%')
			ft_conversion(&pf);
		else
		{
			pf.buf[pf.buf_len++] = *pf.format;
			pf.count++;
		}
		if (pf.buf_len == BUF_SIZE)
			ft_print_buf(&pf);
		pf.format++;
	}
	va_end(pf.ap);
	if (pf.buf_len > 0)
		ft_print_buf(&pf);
	return (pf.count);
}
