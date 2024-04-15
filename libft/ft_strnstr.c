/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:08:25 by sukwon            #+#    #+#             */
/*   Updated: 2023/12/20 11:32:58 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	start;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (len == 0 || ft_strlen(haystack) == 0)
		return (NULL);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		start = i;
		j = 0;
		while (i < len && needle[j] != '\0' && haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)(haystack + start));
		i = start + 1;
	}
	return (NULL);
}
