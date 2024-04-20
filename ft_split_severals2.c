/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:13:01 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/20 12:42:30 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	cmd_count_util(char **str, size_t *i, char s1, char s2)
{
	if (**str == s1)
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
	else if (**str == s2)
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

size_t	cmd_count_words(char *str, char c, char s1, char s2)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		i = cmd_count_util(&str, &i, s1, s2);
		if (*str && *str != c)
		{
			i++;
			while (*str && *str != c)
			{
				if ((*str == s1 || *str == s2))
					break ;
				str++;
			}
		}
		else
			str++;
	}
	return (i);
}

static size_t	get_each_str_quote2(char **str, t_num *num, char s2)
{
	if ((*str)[num->i] == s2)
	{
		(*str)[num->i] = **str;
		(*str)++;
		while ((*str)[num->i] && (*str)[num->i] != s2)
		{
			num->count++;
			if ((*str)[num->i + 1] == '\0')
				return (1);
			else if ((*str)[num->i + 1] == s2)
				return (num->count);
			num->i++;
		}
	}
	return (num->i);
}

static size_t	get_each_str_quote1(char **str, t_num *num, char s1)
{
	if ((*str)[num->i] == s1)
	{
		(*str)++;
		(*str)[num->i] = **str;
		while ((*str)[num->i] && (*str)[num->i] != s1)
		{
			num->count++;
			if ((*str)[num->i + 1] == s1)
				return (num->count);
			num->i++;
		}
	}
	return (num->i);
}

size_t	get_each_str_length(char **str, char c, char s1, char s2)
{
	t_num	num;

	num.count = 0;
	num.i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[num.i] != '\0')
	{
		num.i = get_each_str_quote1(str, &num, s1);
		num.i = get_each_str_quote2(str, &num, s2);
		if ((*str)[num.i] == c)
			return (num.count);
		num.i++;
		num.count++;
	}
	return (num.count);
}
