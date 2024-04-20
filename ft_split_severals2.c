/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:13:01 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/20 17:14:40 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t cmd_count_util(char **str, size_t *i, char s1, char s2)
{
	if (**str && **str == s1)
	{
		(*str)++;
		while (**str && (**str != s1))
			(*str)++;
		(*i)++;
		if (**str == s1)
			(*str)++;
		else if (**str == '\0')
			return ((*i));
	}
	else if (**str && **str == s2)
	{
		(*str)++;
		while (**str && (**str != s2))
		{
			// ft_putstr_fd(" ' : ", 2);
			// ft_putchar_fd(**str, 2);
			// ft_putstr_fd("\n", 2);
			(*str)++;
		}
		(*i)++;
		if (**str == s2)
		{
			// ft_putstr_fd(" the end ' : ", 2);
			// ft_putchar_fd(**str, 2);
			// ft_putstr_fd("\n", 2);
			(*str)++;
		}
		else if (**str == '\0')
		{
			// ft_putstr_fd(" the end '\0' : ", 2);
			// ft_putchar_fd(**str, 2);
			// ft_putstr_fd("\n", 2);

			return ((*i));
		}
	}
	return ((*i));
}

size_t cmd_count_words(char *str, t_split split)
{
	size_t i;

	i = 0;
	while (*str)
	{
		i = cmd_count_util(&str, &i, split.s1, split.s2);
		// ft_putstr_fd("i : ", 2);
		// ft_putnbr_fd(i, 2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("after :", 2);
		// ft_putchar_fd(*str, 2);
		// ft_putstr_fd("\n", 2);
		if (*str && *str != split.c)
		{
			i++;
			// ft_putstr_fd("2 : i : ", 2);
			// ft_putnbr_fd(i, 2);
			// ft_putstr_fd("\n", 2);
			while (*str && *str != split.c)
			{
				// ft_putstr_fd("until the space -char :", 2);
				// ft_putchar_fd(*str, 2);
				// ft_putstr_fd("\n", 2);
				if ((*str == split.s1 || *str == split.s2))
				{
					// 	ft_putstr_fd("met :", 2);
					// 	ft_putchar_fd(*str, 2);
					// 	ft_putstr_fd("\n", 2);
					break;
				}
				str++;
			}
		}
		else if (*str && *str == split.c)
			str++;
	}
	return (i);
}

static size_t get_each_str_quote(char **str, t_num *num, char s2, int *check)
{
	if ((*str)[num->i] && (*str)[num->i] == s2)
	{
		*check = 0;
		(*str)[num->i] = **str;
		(*str)++;
		ft_putstr_fd("2:: ' : **str : ", 2);
		ft_putchar_fd(**str, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("2:: ' : (*str)[i] : ", 2);
		ft_putchar_fd((*str)[num->i], 2);
		ft_putstr_fd("\n", 2);
		while ((*str)[num->i] && (*str)[num->i] != s2)
		{
			ft_putstr_fd("2:: until the \' -char :", 2);
			ft_putchar_fd((*str)[num->i], 2);
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("2:: i :", 2);
			ft_putnbr_fd(num->i, 2);
			ft_putstr_fd("\n", 2);
			num->count++;
			ft_putstr_fd("2:: count :", 2);
			ft_putnbr_fd(num->count, 2);
			ft_putstr_fd("\n", 2);
			num->i++;
			if ((*str)[num->i] == '\0')
				return (-1);
			else if ((*str)[num->i] == s2)
			{
				ft_putstr_fd("2:: ' :", 2);
				ft_putchar_fd((*str)[num->i], 2);
				ft_putstr_fd("\n", 2);
				*check = -10;
				ft_putstr_fd("check : ", 2);
				ft_putnbr_fd(*check, 2);
				ft_putstr_fd("\n", 2);
				// num->i++;
				return (-2);
			}
		}
	}
	return (num->count);
}

// static size_t get_each_str_quote1(char **str, t_num *num, t_split *split)
// {
// 	if ((*str)[num->i] && (*str)[num->i] == split->1)
// 	{
// 		(*str)++;
// 		(*str)[num->i] = **str;
// 		while ((*str)[num->i] && (*str)[num->i] != split->s1)
// 		{
// 			num->count++;
// 			num->i++;
// 			if ((*str)[num->i] == '\0')
// 				return (-1);
// 			else if ((*str)[num->i] == split->s1)
// 				return (num->count - 1);
// 		}
// 	}
// 	return (num->count);
// }

size_t get_each_str_length(char **str, t_split *split)
{
	t_num num;

	num.count = 0;
	num.i = 0;
	num.res = 0;
	// num.check = 0;
	while (**str && (**str == split->c))
		(*str)++;
	while ((*str)[num.i])
	{
		num.res = get_each_str_quote(str, &num, split->s1, &split->check);
		if (num.res == -1)
			return (1);
		if (num.res == -2)
			return (num.count);
		ft_putstr_fd("num.res : ", 2);
		ft_putnbr_fd(num.res, 2);
		ft_putstr_fd("\n", 2);
		num.res = get_each_str_quote(str, &num, split->s2, &split->check);
		ft_putstr_fd("split_check : ", 2);
		ft_putnbr_fd(split->check, 2);
		ft_putstr_fd("\n", 2);
		if (num.res == -1)
			return (num.res);
		if (num.res == -2)
			return (num.count);
		ft_putstr_fd("char :: ", 2);
		ft_putchar_fd((*str)[num.i], 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("num.i : ", 2);
		ft_putnbr_fd(num.i, 2);
		ft_putstr_fd("\n", 2);
		if ((*str)[num.i] == split->c)
		{
			ft_putstr_fd("space :: ", 2);
			ft_putchar_fd((*str)[num.i], 2);
			ft_putstr_fd("\n", 2);
			return (num.count);
		}
		num.i++;
		num.count++;
		ft_putstr_fd("char :: ", 2);
		ft_putchar_fd((*str)[num.i], 2);
		ft_putstr_fd("\n", 2);
	}
	// ft_putstr_fd("num.check : ", 2);
	// ft_putnbr_fd(num.check, 2);
	// ft_putstr_fd("\n", 2);
	// split->check = num.check;
	// ft_putstr_fd("split_check : ", 2);
	// ft_putnbr_fd(split->check, 2);
	// ft_putstr_fd("\n", 2);
	return (num.count);
}