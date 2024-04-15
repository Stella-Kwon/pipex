/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:54:36 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/17 13:03:25 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier(t_print *print, char format)
{
	if (format == 'c')
		return (put_char(print, va_arg((print)->ap, int)));
	else if (format == 's')
		return (put_str(print, va_arg((print)->ap, char *)));
	else if (format == 'p')
		return (put_ptr(print, va_arg((print)->ap, void *)));
	else if (format == 'd' || format == 'i')
		return (put_num(print, va_arg((print)->ap, int)));
	else if (format == 'u')
		return (put_num_unsigned(print, va_arg((print)->ap, unsigned int)));
	else if (format == 'x')
		return (put_hex(print, va_arg((print)->ap, unsigned int), 'a'));
	else if (format == 'X')
		return (put_hex_cap(print, va_arg((print)->ap, unsigned int), 'A'));
	else if (format == '%')
	{
		if (put_char(print, '%') == -1)
			return (-1);
	}
	return ((print)->len);
}

int	errcheck(t_print *print, int n)
{
	if (n == -1)
	{
		va_end((print)->ap);
		return (-1);
	}
	return ((print)->len);
}

int	ft_printf(const char *fm, ...)
{
	t_print	print;

	print.len = 0;
	va_start(print.ap, fm);
	while (*fm)
	{
		if (*fm == '%')
		{
			if (errcheck(&print, specifier(&print, *(++fm))) == -1)
				return (-1);
		}
		else if (*fm)
		{
			if (errcheck(&print, put_char(&print, *fm)) == -1)
				return (-1);
		}
		fm++;
	}
	va_end(print.ap);
	return (print.len);
}
