/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:29:36 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/15 17:43:36 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_num(t_print *print, int n)
{
	int	num;

	num = n;
	if (num == -2147483648)
	{
		if (put_char(print, '-') == -1)
			return (-1);
		if (put_char(print, '2') == -1)
			return (-1);
		num = 147483648;
	}
	if (num < 0)
	{
		if (put_char(print, '-') == -1)
			return (-1);
		num *= -1;
	}
	if (put_num_unsigned(print, num) == -1)
		return (-1);
	return ((print)->len);
}

int	put_num_unsigned(t_print *print, unsigned int n)
{
	if (n >= 0 && n < 10)
	{
		if (put_char(print, '0' + n) == -1)
			return (-1);
	}
	else if (n >= 10)
	{
		if (put_num_unsigned(print, n / 10) == -1)
			return (-1);
		if (put_num_unsigned(print, n % 10) == -1)
			return (-1);
	}
	return ((print)->len);
}
