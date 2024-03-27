/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:29:51 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/15 17:42:44 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_char(t_print *print, char c)
{
	int	length;

	length = write(1, &c, 1);
	if (length == -1)
		return (-1);
	else
		(print)->len += 1;
	return ((print)->len);
}

int	put_str(t_print *print, char *s)
{
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		(print)->len += 6;
		return ((print)->len);
	}
	while (*s)
	{
		if (put_char(print, *s) == -1)
			return (-1);
		s++;
	}
	return ((print)->len);
}
