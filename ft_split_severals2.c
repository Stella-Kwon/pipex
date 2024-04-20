/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:13:01 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/20 17:19:06 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	cmd_count_util(char **str, size_t *i, char s1, char s2)
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
			(*str)++;
		(*i)++;
		if (**str == s2)
			(*str)++;
		else if (**str == '\0')
			return ((*i));
	}
	return ((*i));
}

size_t	cmd_count_words(char *str, t_split split)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		i = cmd_count_util(&str, &i, split.s1, split.s2);
		if (*str && *str != split.c)
		{
			i++;
			while (*str && *str != split.c)
			{
				if ((*str == split.s1 || *str == split.s2))
					break ;
				str++;
			}
		}
		else if (*str && *str == split.c)
			str++;
	}
	return (i);
}

static size_t	get_each_str_quote(char **str, t_num *num, char s2, int *check)
{
	if ((*str)[num->i] && (*str)[num->i] == s2)
	{
		*check = 0;
		(*str)[num->i] = **str;
		(*str)++;
		while ((*str)[num->i] && (*str)[num->i] != s2)
		{
			num->count++;
			num->i++;
			if ((*str)[num->i] == '\0')
				return (-1);
			else if ((*str)[num->i] == s2)
			{
				*check = -10;
				return (-2);
			}
		}
	}
	return (num->count);
}

size_t	get_each_str_length(char **str, t_split *split)
{
	t_num	num;

	num.count = 0;
	num.i = 0;
	num.res = 0;
	while (**str && (**str == split->c))
		(*str)++;
	while ((*str)[num.i])
	{
		num.res = get_each_str_quote(str, &num, split->s1, &split->check);
		if (num.res == -1)
			return (1);
		if (num.res == -2)
			return (num.count);
		num.res = get_each_str_quote(str, &num, split->s2, &split->check);
		if (num.res == -1)
			return (num.res);
		if (num.res == -2)
			return (num.count);
		if ((*str)[num.i] == split->c)
			return (num.count);
		num.i++;
		num.count++;
	}
	return (num.count);
}
