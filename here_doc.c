/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:18 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/20 09:08:15 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *line, const char *limiter)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(limiter);
	if ((ft_strlen(line)) != n)
		return (-1);
	while (i < n && (line[i] != '\0' || limiter[i] != '\0'))
	{
		if ((unsigned char)limiter[i] != (unsigned char)line[i])
			return (-2);
		i++;
	}
	return (0);
}

int	heredoc_child(int fd, char *limiter)
{
	char	*line;

	line = NULL;
	while (read_line(&line) != FAILED)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			line = ft_strjoin(line, "\n");
			if (!line)
				return (errors("read-line ft_strjoin error", 0, NULL, NULL));
			else
				free(line);
			close(fd);
			return (SUCCESS);
		}
		line = ft_strjoin(line, "\n");
		if (write(fd, line, ft_strlen(line)) == -1)
			errors("write", 0, NULL, NULL);
		free(line);
		line = NULL;
		ft_putstr_fd("> ", 0);
	}
	return (FAILED);
}

int	here_doc(char *limiter, t_data *data)
{
	t_doc	heredoc;

	heredoc.wstatus = -1;
	if (data->argc < 6)
		return (error_syntax(1));
	data->infile = open_file(".tmp", 1, 1);
	if (data->infile == -1)
		return (FAILED);
	ft_putstr_fd("> ", 0);
	heredoc.exitcode = heredoc_child(data->infile, limiter);
	close(data->infile);
	data->infile = open_file(".tmp", 0, 0);
	if (data->infile == -1)
		return (FAILED);
	return (heredoc.exitcode);
}

int	check_heredoc(t_data *data)
{
	if (ft_strcmp(data->argv[1], "here_doc") == 0)
	{
		if (here_doc(data->argv[2], data) != SUCCESS)
			return (FAILED);
		data->start = 3;
		data->checkheredoc = 1;
	}
	else
		data->start = 2;
	return (SUCCESS);
}
