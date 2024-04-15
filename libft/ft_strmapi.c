/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:44:10 by sukwon            #+#    #+#             */
/*   Updated: 2023/12/20 10:22:14 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = f(i, res[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
