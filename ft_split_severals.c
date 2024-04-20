/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:04:45 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/20 12:30:09 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**get_res(char *str, char c, char s1, char s2)
{
	char	**res;
	size_t	each_strlen;
	size_t	i;
	size_t	res_len;

	res_len = cmd_count_words(str, c, s1, s2);
	res = (char **)malloc((res_len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < res_len)
	{
		each_strlen = get_each_str_length(&str, c, s1, s2);
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
