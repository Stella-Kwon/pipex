/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_several.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:42:49 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/14 17:50:37 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// #include "libft/libft.h"
// #include <string.h>
// # include <unistd.h>
// # include <fcntl.h>
// # include <stdio.h>
// # include <stdlib.h>

// static size_t	count_words(char *str, char c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*str)
// 	{
// 		if (*str != c)
// 		{
// 			i++;
// 			while (*str && *str != c)
// 				str++;
// 		}
// 		else
// 			str++;
// 	}
// 	return (i);
// }

static size_t	get_each_strlen(char **str, char c, char s1, char s2)
{
	size_t	i;

	i = 0;
	while (**str && (**str == c || **str == s1 || **str == s2)) // 앞에 있는 스페이스를 옮겨주기위해서, 포인터를 옮겨주는것은 위치를 옮겨주기위해서. 후의 위치를 바꿔주기위해서)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c || (*str)[i] == s1 || (*str)[i] == s2)
			break ;
		i++;
	}
	return (i);
}

// static char	**all_free(char ***res)
// {
// 	int	i;

// 	i = 0;
// 	while ((*res)[i])
// 	{
// 		free ((*res)[i]);
// 		(*res)[i] = NULL;
// 		i++;
// 	}
// 	free(*res);
// 	*res = NULL;
// 	return (NULL);
// }

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

// int main (int argc, char **argv)
// {
// 	char **res;
// 	int	i;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		printf("argv[%d] : %s\n", i, argv[i]);
// 		res = ft_split_several(argv[i], ' ', '"', '\'');
// 		int s = 0;
// 		while (res[s])
// 		{
// 			printf("res[%d] : %s\n", s, res[s]);
// 			s++;
// 		}
// 		i ++;
// 	}


// 	return (0);
// }
