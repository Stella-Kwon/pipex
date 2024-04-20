/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_severals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:04:45 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/20 17:20:26 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	**get_res(char *str, t_split split)
{
	size_t	i;

	split.res_len = cmd_count_words(str, split);
	split.res = (char **)malloc((split.res_len + 1) * sizeof(char *));
	if (!split.res)
		return (NULL);
	i = 0;
	while (i < split.res_len)
	{
		split.each_strlen = get_each_str_length(&str, &split);
		split.res[i] = (char *)malloc((split.each_strlen + 1) * sizeof(char));
		if (!split.res[i])
			return (all_free(&split.res));
		ft_strlcpy(split.res[i], str, split.each_strlen + 1);
		str += split.each_strlen;
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
