/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:04:45 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/20 15:13:09 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**get_res(char *str, t_split split)
{
	// char	**res;
	// size_t	each_strlen;
	size_t	i;
	// size_t	res_len;

	split.res_len = cmd_count_words(str, split);
	ft_putstr_fd("cmd counts : ", 2);
	ft_putnbr_fd(split.res_len, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("\n", 2);
	split.res = (char **)malloc((split.res_len + 1) * sizeof(char *));
	if (!split.res)
		return (NULL);
	i = 0;
	while (i < split.res_len)
	{
		split.each_strlen = get_each_str_length(&str, &split);
		ft_putstr_fd("character counts : ", 2);
		ft_putnbr_fd(split.each_strlen, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\n", 2);
		split.res[i] = (char *)malloc((split.each_strlen + 1) * sizeof(char));
		if (!split.res[i])
			return (all_free(&split.res));
		ft_strlcpy(split.res[i], str, split.each_strlen + 1);
		str += split.each_strlen;
		ft_putstr_fd("split_check : ", 2);
		ft_putnbr_fd(split.check, 2);
		ft_putstr_fd("\n", 2);
		if (split.check == -10)
			str ++;
		i++;
	}
	split.res[i] = NULL;
	return (split.res);
}

char	**ft_split_several(char const *s, const char c, \
const char s1, const char s2)
{
	char		**res;
	char		*str;
	t_split		split;

	split.c = c;
	split.s1 = s1;
	split.s2 = s2;
	split.check = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	res = get_res(str, split);
	return (res);
}
