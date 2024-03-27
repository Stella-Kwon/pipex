/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:18:45 by sukwon            #+#    #+#             */
/*   Updated: 2023/12/22 13:10:32 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*temp;
	char	*start;
	char	*end;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = (char *)s1;
	end = start + ft_strlen(s1) - 1;
	while (*start && find_set(*start, set))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	while (*end && find_set(*end, set))
		end--;
	len = end - start + 1;
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, start, len + 1);
	return (temp);
}
