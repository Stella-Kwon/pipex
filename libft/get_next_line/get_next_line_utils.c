/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:40 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/18 12:57:13 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_one(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *previous_read, char const *buffer)
{
	char	*res;
	size_t	whole_len;
	size_t	i;
	size_t	j;

	if (!previous_read)
		previous_read = ft_strdup("");
	if (!previous_read)
		return (NULL);
	if (buffer[0] == '\0')
		return (previous_read);
	whole_len = ft_strlen(previous_read) + ft_strlen(buffer);
	res = (char *)malloc(sizeof(char) * (whole_len + 1));
	if (!res)
		return (free_one(&previous_read));
	i = -1;
	while (previous_read[++i])
		res[i] = previous_read[i];
	j = 0;
	while (buffer[j])
		res[i++] = buffer[j++];
	res[whole_len] = '\0';
	previous_read = free_one(&previous_read);
	return (res);
}
