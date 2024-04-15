/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:04:45 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/15 10:38:01 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	get_each_strlen(char **str, char c, char s1, char s2)
{
	size_t	i;

	i = 0;
	while (**str && (**str == c || **str == s1 || **str == s2))
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c || (*str)[i] == s1 || (*str)[i] == s2)
			break ;
		i++;
	}
	return (i);
}

static char	**get_res(char *str, char c, char s1, char s2)
{
	char	**res;
	size_t	each_strlen;
	size_t	i;
	size_t	res_len;

	res_len = count_words(str, c);
	res = (char **)malloc((res_len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < res_len)
	{
		each_strlen = get_each_strlen(&str, c, s1, s2);
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
