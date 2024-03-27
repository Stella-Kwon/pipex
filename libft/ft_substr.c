/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:54:13 by skwon2            #+#    #+#             */
/*   Updated: 2023/12/22 13:10:37 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getmin(size_t	len, size_t	max)
{
	if (len < max)
		return (len);
	else
		return (max);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	min;
	unsigned int	slen;
	unsigned int	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start || len == 0)
		return (ft_strdup(""));
	min = getmin(len, slen - start);
	res = (char *)malloc(min + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < min)
	{
		res[i++] = s[start++];
	}
	res[i] = '\0';
	return (res);
}

// int main(void)
// {
// 	// const char s[ 2147483647] = "ㄴㄴㄴ";	//stackoverflow error occur
// 	const char *s = "hello";
// 	unsigned int start = 2;
// 	size_t len = 5;
// 	char *res = ft_substr(s,start, len);
// 	printf("\n\n%s",res);
// 	free(res);
// 	return 0;
// }