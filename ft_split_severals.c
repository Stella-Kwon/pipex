/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:04:45 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/15 20:30:07 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	cmd_count_words(char *str, char c, char s1, char s2)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str != c || *str == s1 || *str == s2)
		{
			ft_putstr_fd("i : ",2);
			ft_putnbr_fd(i,2);
			ft_putstr_fd("\n",2);
			i++;
			if (*str == s1)
			{
				while (*str && (*str != s1 && *(str + 1) == s1))
				{
					ft_putstr_fd("\" : ", 2);
					ft_putchar_fd(*str, 2);
					ft_putstr_fd("\n", 2);
					str++;
				}
			}
			else if (*str == s2)
			{
				while (*str && (*str != s2 && *(str + 1) == s2))
				{
					ft_putstr_fd(" ' : ", 2);
					ft_putchar_fd(*str, 2);
					ft_putstr_fd("\n", 2);
					str++;
				}
			}
			while (*str && *str != c)
			{
				ft_putstr_fd("until the space -char :", 2);
				ft_putchar_fd(*str, 2);
				ft_putstr_fd("\n", 2);
				str++;
			}
			i++;
			while (*str &&  (*str != s1 || *str != s2))
			{
				ft_putstr_fd("until the \" -char :", 2);
				ft_putchar_fd(*str, 2);
				ft_putstr_fd("\n", 2);
				str++;
			}
		}
		else
		{
			ft_putstr_fd("space : ", 2);
			ft_putchar_fd(*str, 2);
			ft_putstr_fd("\n", 2);
			str++;

		}
	}
	return (i);
}

static size_t	get_each_strlen(char **str, char c, char s1, char s2)
{
	size_t	i;

	i = 0;
// 	while (**str && **str == c)
// 	{
// 		ft_putstr_fd("space :", 2);
// 		ft_putchar_fd(**str, 2);
// 		ft_putstr_fd("\n", 2);
// 		(*str)++;
// 	}
// 	while ((*str)[i])
// 	{
// 		ft_putstr_fd("character :", 2);
// 		ft_putchar_fd(**str, 2);
// 		ft_putstr_fd("\n", 2);
// 		if (**str == s1)
// 		{
// 			ft_putstr_fd("2:: \" :", 2);
// 			ft_putchar_fd(**str, 2);
// 			ft_putstr_fd("\n", 2);
// 			(*str)++;
// 			while (**str && (**str != s1 && **(str + 1) == s1))
// 			{
// 				ft_putstr_fd("2:: until the \" -char :", 2);
// 				ft_putchar_fd(**str, 2);
// 				ft_putstr_fd("\n", 2);
// 				i++;
// 				(*str)++;
// 			}
// 			return (i);
// 		}
// 		else if (**str == s2)
// 		{
// 			ft_putstr_fd("2:: ' :", 2);
// 			ft_putchar_fd(**str, 2);
// 			ft_putstr_fd("\n", 2);
// 			(*str)++;
// 			while (**str && (**str != s2 && **(str + 1) == s2))
// 			{
// 				ft_putstr_fd("2:: until the ' -char :", 2);
// 				ft_putchar_fd(**str, 2);
// 				ft_putstr_fd("\n", 2);
// 				i++;
// 				(*str)++;
// 			}
// 			return (i);
// 		}
// 		while (**str == c)
// 		{
// 			ft_putstr_fd("space :", 2);
// 			ft_putchar_fd(**str, 2);
// 			ft_putstr_fd("\n", 2);
// 			(*str)++;
// 			break;
// 		}
// 		(*str)++;
// 		i++;
// 	}
// 	return (i);
// }

./pipex input "grep "Hello"" "awk '{count++} END {print count}'" output

	while (**str)
	{
		while (**str && **str == c)
		{
			ft_putstr_fd("space : ", 2);
			ft_putchar_fd(**str, 2);
			ft_putstr_fd("\n", 2);
			(*str)++;
		}
		if (**str != c || **str == s1 || **str == s2)
		{

			if (**str == s1)
			{
				while (**str && (**str != s1 && **(str + 1) == s1))
				{
					ft_putstr_fd("\" : ", 2);
					ft_putchar_fd(**str, 2);
					ft_putstr_fd("\n", 2);
					(*str)++;
					i++;
					// return (i);
					break;
				}
			}
			else if (**str == s2)
			{
				while (**str && (**str != s2 && **(str + 1) == s2))
				{
					ft_putstr_fd(" ' : ", 2);
					ft_putchar_fd(**str, 2);
					ft_putstr_fd("\n", 2);
					(*str)++;
					i++;
					// return (i);
					break;
				}
			}
			while (**str && **str != c)
			{
				ft_putstr_fd("until the space -char :", 2);
				ft_putchar_fd(**str, 2);
				ft_putstr_fd("\n", 2);
				(*str)++;
				i++;
			}
			while (**str && (**str != s1 || **str != s2))
			{
				ft_putstr_fd("until the \" -char :", 2);
				ft_putchar_fd(**str, 2);
				ft_putstr_fd("\n", 2);
				(*str)++;
				i++;
			}
			if (**str && **str == c)
			{
				(*str)++;
				break;
			}
		}
	ft_putstr_fd("i : ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("\n", 2);
	}
	return (i);
}

static char	**get_res(char *str, char c, char s1, char s2)
{
	char	**res;
	size_t	each_strlen;
	size_t	i;
	size_t	res_len;

	res_len = cmd_count_words(str, c, s1, s2);
	ft_putstr_fd("cmd counts : ", 2);
	ft_putnbr_fd(res_len,2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("\n", 2);
	res = (char **)malloc((res_len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < res_len)
	{
		each_strlen = get_each_strlen(&str, c, s1, s2);
		ft_putstr_fd("character counts : ", 2);
		ft_putnbr_fd(each_strlen,2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\n", 2);
		res[i] = (char *)malloc((each_strlen + 1) * sizeof(char));
		if (!res[i])
			return (all_free(&res));
		ft_strlcpy(res[i], str, each_strlen + 1);
		str += each_strlen;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split_several(char const *s, char c, char s1, char s2)
{
	char	**res;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	res = get_res(str, c, s1, s2);
	return (res);
}
