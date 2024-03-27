/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:03:43 by suminkwon         #+#    #+#             */
/*   Updated: 2024/01/18 13:04:45 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*free_both(char **previous_read, char **buffer)
{
	if (previous_read && *previous_read)
	{
		free(*previous_read);
		*previous_read = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

static char	*find_newline(char *previous_read, int fd)
{
	char	*buffer;
	int		readsize;

	readsize = 1;
	while (readsize && !ft_strchr(previous_read, '\n'))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (free_one(&previous_read));
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize == -1)
			return (free_both(&previous_read, &buffer));
		buffer[readsize] = '\0';
		previous_read = ft_strjoin_gnl(previous_read, buffer);
		buffer = free_one(&buffer);
	}
	return (previous_read);
}

static int	store_line(char *previous_read, char **line)
{
	size_t	i;

	i = 0;
	if (!previous_read[i])
		return (-1);
	while (previous_read[i] && previous_read[i] != '\n')
		i++;
	if (previous_read[i] == '\n')
		i++;
	*line = (char *)malloc(sizeof(char) * (i + 1));
	if (!*line)
		return (-1);
	i = 0;
	while (previous_read[i] && previous_read[i] != '\n')
	{
		(*line)[i] = previous_read[i];
		i++;
	}
	if (previous_read[i] == '\n')
	{
		(*line)[i] = previous_read[i];
		i++;
	}
	(*line)[i] = '\0';
	return (0);
}

static char	*store_leftover(char *previous_read)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_previous_read;

	i = 0;
	while (previous_read[i] != '\n' && previous_read[i] != '\0')
		i++;
	if (!previous_read[i])
		return (free_one(&previous_read));
	len = (ft_strlen(previous_read) - i + 1);
	new_previous_read = (char *)malloc(sizeof(char) * len + 1);
	if (!new_previous_read)
		return (free_one(&previous_read));
	++i;
	j = 0;
	while (previous_read[i])
		new_previous_read[j++] = previous_read[i++];
	new_previous_read[j] = '\0';
	previous_read = free_one(&previous_read);
	return (new_previous_read);
}

char	*get_next_line(int fd)
{
	static char	*previous_read[OPEN_MAX];
	char		*line;

	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0)
	{
		if (previous_read[fd])
			return (free_one(&previous_read[fd]));
	}
	previous_read[fd] = find_newline(previous_read[fd], fd);
	if (!previous_read[fd])
		return (NULL);
	if (store_line(previous_read[fd], &line) < 0)
		return (free_one(&previous_read[fd]));
	previous_read[fd] = store_leftover(previous_read[fd]);
	return (line);
}
