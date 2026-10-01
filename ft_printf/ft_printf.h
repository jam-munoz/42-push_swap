/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:52:57 by joamunoz          #+#    #+#             */
/*   Updated: 2026/09/02 12:43:33 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# define BUF_SIZE 1024

typedef struct s_printf
{
	va_list		ap;
	const char	*format;
	char		buf[BUF_SIZE];
	int			buf_len;
	int			count;
}	t_printf;

int		ft_printf(const char *format, ...);
void	ft_print_buf(t_printf *pf);
void	ft_print_int(t_printf *pf);
void	ft_print_uint(t_printf *pf);
void	ft_print_hex(t_printf *pf);
void	ft_print_ptr(t_printf *pf);

#endif
