/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:48:20 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/24 08:26:58 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	ft_print_buf(t_printf *pf)
{
	write(pf->fd, pf->buf, pf->buf_len);
	pf->count += pf->buf_len;
	pf->buf_len = 0;
}

static void	ft_print_str(t_printf *pf)
{
	char	*str;

	str = va_arg(pf->ap, char *);
	if (!str)
		str = "(null)";
	while (*str)
	{
		pf->buf[pf->buf_len++] = *str++;
		if (pf->buf_len == BUF_SIZE)
			ft_print_buf(pf);
	}
}

static void	ft_conversion(t_printf *pf)
{
	pf->format++;
	if (*pf->format == 'l' && *(pf->format + 1) == 'd')
	{
		pf->format++;
		ft_print_long(pf);
	}
	else if (*pf->format == 'd' || *pf->format == 'i')
		ft_print_int(pf);
	else if (*pf->format == 's')
		ft_print_str(pf);
	else if (*pf->format == 'f')
		ft_print_float(pf);
	else if (*pf->format == 'c')
		pf->buf[pf->buf_len++] = (char)va_arg(pf->ap, int);
	else if (*pf->format == 'u')
		ft_print_uint(pf);
	else if (*pf->format == 'x' || *pf->format == 'X')
		ft_print_hex(pf);
	else if (*pf->format == '%')
		pf->buf[pf->buf_len++] = '%';
	else if (*pf->format == 'p')
		ft_print_ptr(pf);
}

static void	ft_process_format(t_printf *pf)
{
	while (*pf->format != '\0')
	{
		if (*pf->format == '%')
			ft_conversion(pf);
		else
			pf->buf[pf->buf_len++] = *pf->format;
		if (pf->buf_len == BUF_SIZE)
			ft_print_buf(pf);
		pf->format++;
	}
	if (pf->buf_len > 0)
		ft_print_buf(pf);
}

int	ft_printf(int fd, const char *format, ...)
{
	t_printf	pf;

	pf.format = format;
	pf.buf_len = 0;
	pf.count = 0;
	pf.fd = fd;
	va_start(pf.ap, format);
	ft_process_format(&pf);
	va_end(pf.ap);
	return (pf.count);
}
