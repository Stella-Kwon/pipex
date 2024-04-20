/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:04:45 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/20 08:58:51 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t cmd_count_words(char *str, char c, char s1, char s2)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str == s1)
		{
			str++;
			while (*str && (*str != s1))
			{
				// ft_putstr_fd("\" : ", 2);
				// ft_putchar_fd(*str, 2);
				// ft_putstr_fd("\n", 2);
				str++;
			}
			i++;
			if (*(str) == s1)
				str++;
			else if (*(str) == '\0')
				break ;
			// ft_putstr_fd("i : ", 2);
			// ft_putnbr_fd(i, 2);
			// ft_putstr_fd("\n", 2);
		}
		else if (*str == s2)
		{
			str++;
			while (*str && (*str != s2))
			{
				// ft_putstr_fd(" ' : ", 2);
				// ft_putchar_fd(*str, 2);
				// ft_putstr_fd("\n", 2);
				str++;
			}
			i++;
			if (*(str) == s2)
				str++;
			else if (*(str) == '\0')
				break ;
			// ft_putstr_fd("i : ", 2);
			// ft_putnbr_fd(i, 2);
			// ft_putstr_fd("\n", 2);
		}
		if (*str && *str != c)
		{
			i++;
			// ft_putstr_fd("i : ", 2);
			// ft_putnbr_fd(i, 2);
			// ft_putstr_fd("\n", 2);
			while (*str && *str != c)
			{
				// ft_putstr_fd("until the space -char :", 2);
				// ft_putchar_fd(*str, 2);
				// ft_putstr_fd("\n", 2);
				if ((*str == s1 || *str == s2))
				{
					ft_putstr_fd("met :", 2);
					ft_putchar_fd(*str, 2);
					ft_putstr_fd("\n", 2);
					break ;
				}
				str++;
			}
		}
		else
		{
			// ft_putstr_fd("space : ", 2);
			// ft_putchar_fd(*str, 2);
			// ft_putstr_fd("\n", 2);
			str++;
		}
	}
	return (i);
}

static size_t	get_each_strlen(char **str, char c, char s1, char s2)
{
	size_t	count;
	int		i;
	// char	*res;
	// char	*line;

	count = 0;
	i = 0;
	// res = NULL;
	// line = NULL;
	while (**str && **str == c)
	{
		// ft_putstr_fd("space :", 2);
		// ft_putchar_fd(**str, 2);
		// ft_putstr_fd("\n", 2);
		(*str)++;
	}
	while ((*str)[i] != '\0')
	{
		// ft_putstr_fd("character :", 2);
		// ft_putchar_fd((*str)[i], 2);
		// ft_putstr_fd("\n", 2);
		if ((*str)[i] == s1)
		{
			(*str)++;
			(*str)[i] = **str;
			// ft_putstr_fd("2:: \" :", 2);
			// ft_putchar_fd(**str, 2);
			// ft_putstr_fd("\n", 2);
			// ft_putstr_fd("2:: \" :", 2);
			// ft_putchar_fd((*str)[i], 2);
			// ft_putstr_fd("\n", 2);
			while ((*str)[i] && (*str)[i] != s1)
			{
				// ft_putstr_fd("2:: until the \" -char :", 2);
				// ft_putchar_fd((*str)[i], 2);
				// ft_putstr_fd("\n", 2);
				// ft_putstr_fd("2:: i :", 2);
				// ft_putchar_fd(i, 2);
				// ft_putstr_fd("\n", 2);
				count++;
				if ((*str)[i + 1] == s1)
					return (count);
				i++;
			}
		}
		else if ((*str)[i] == s2)
		{
			(*str)[i] = **str;
			(*str)++;
			// ft_putstr_fd("2:: ' : **str : ", 2);
			// ft_putchar_fd(**str, 2);
			// ft_putstr_fd("\n", 2);
			// ft_putstr_fd("2:: ' : (*str)[i] : ", 2);
			// ft_putchar_fd((*str)[i], 2);
			// ft_putstr_fd("\n", 2);
			// i++; //이렇게하면 한번더가서 안됌. 이미 ++str의 위치는 달라져있기때문에.
			while ((*str)[i] && (*str)[i] != s2)
			{
				// ft_putstr_fd("2:: until the \' -char :", 2);
				// ft_putchar_fd((*str)[i], 2);
				// ft_putstr_fd("\n", 2);
				// ft_putstr_fd("2:: i :", 2);
				// ft_putnbr_fd(i, 2);
				// ft_putstr_fd("\n", 2);
				count++;
				if ((*str)[i + 1] == '\0')
				{
					// ft_putstr_fd("the end : ", 2);
					// ft_putchar_fd((*str)[i + 1], 2);
					// ft_putstr_fd("\n", 2);
					// ft_putstr_fd(">", 2);
					// while (read_line(&line) != FAILED)
					// {
						// if (write(0, line, ft_strlen(line)) == -1)
						// 	errors("write", 0, NULL, NULL);
						// if (ft_strcmp(line, "'") == 0)
						// {
						// 	// line = ft_strjoin(line, "\n");
						// 	ft_putstr_fd("the strcmp : ", 2);
						// 	if (!line)
						// 		return (errors("read-line ft_strjoin error", 0, NULL, NULL));
						// 	else
						// 		free(line);
						// 	// close(fd);
						// 	// return (SUCCESS);
						// 	break;
						// }
						// else 
						// {
							// res = ft_strdup(*str);
							// // ft_putstr_fd(line, 2);
							// res = ft_strjoin(*str, line);
							// *str = res;
							// // ft_putstr_fd(res, 2);
							// free(res);
							// res = NULL;
							// free(line);
							// line = NULL;
						// }
					// }
					return (1);
				}
				else if ((*str)[i + 1] == s2)
					return (count);
				i++;
			}
		}
		if ((*str)[i] == c)
		{
			// ft_putstr_fd("space :", 2);
			// ft_putchar_fd(**str, 2);
			// ft_putstr_fd("\n", 2);
			return (count);
		}
		// ft_putstr_fd("2:: char :", 2);
		// ft_putchar_fd((*str)[i], 2);
		// ft_putstr_fd("\n", 2);
		i++;
		count++;
	}
	return (count);
}

// ./pipex input "grep "Hello"" "awk '{count++} END {print count}'" output

static char	**get_res(char *str, char c, char s1, char s2)
{
	char	**res;
	size_t	each_strlen;
	size_t	i;
	size_t	res_len;

	res_len = cmd_count_words(str, c, s1, s2);
	// ft_putstr_fd("cmd counts : ", 2);
	// ft_putnbr_fd(res_len,2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("\n", 2);
	res = (char **)malloc((res_len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < res_len)
	{
		each_strlen = get_each_strlen(&str, c, s1, s2);
		// ft_putstr_fd("character counts : ", 2);
		// ft_putnbr_fd(each_strlen,2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("\n", 2);
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
