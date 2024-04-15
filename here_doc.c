/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:18 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 22:17:48 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_one(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

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
		if (write(fd, line, ft_strlen(line) + 1) == -1)
			errors("write", 0, NULL, NULL);
		if (write(fd, "\n", 1) == -1)
			errors("write", 0, NULL, NULL);
		free(line);
		line = NULL; // 이렇게 안하면 쓰레기 갑이 들어감.
		ft_putstr_fd("> ", 0);
	}
	return (FAILED);
}

int	here_doc(char *limiter, t_data *data)
{
	t_doc heredoc;

	heredoc.wstatus = -1;
	if (data->argc < 6)
		return (error_syntax(1));
	// heredoc.fd = open_file("tmp", 3, 1);
	// heredoc.fd = open_file(".tmp", 1, 0);
	// if (heredoc.fd == -1)
		// return (FAILED);
	data->infile = open_file(".tmp", 1, 0); // 다르게 줘도 리드모드가 계속 살아있는걸로나와서..
	if (data->infile == -1)
		return (FAILED);
	// heredoc.pid = fork();
	// if (heredoc.pid == -1)
	// 	return (errors("heredoc.pid", 0, NULL, NULL));
	// if (heredoc.pid == 0)
	// {
		ft_putstr_fd("> ", 0);
		heredoc.exitcode = heredoc_child(data->infile, limiter);
		// data->infile = heredoc.fd;
		// close(heredoc.fd);
		// ft_putstr_fd("data->infile :",2);
		// ft_putnbr_fd(data->infile, 2);
		// 	ft_putstr_fd("heredoc.fd :",2);
		// ft_putnbr_fd(heredoc.fd, 2);

		//////////////
		close(data->infile); // Close the file descriptor for write "tmp"
		// getchar();
		data->infile = open_file(".tmp", 0, 0);
		if (data->infile == -1)
			return (FAILED);

		// heredoc.fd = open_file(".tmp", 0, 0);
		// if (heredoc.fd == -1)
		// 	return (FAILED);
		// if (dup2(heredoc.fd, STDIN_FILENO) == -1)
		// 	return (errors("heredoc_dup2", 0, NULL, NULL)); 
		// data->infile = heredoc.fd;
		// close(heredoc.fd);
		// if (unlink("tmp") == -1) 
		// 	return (errors("Failed to unlink file", 0, NULL, NULL));
	return (heredoc.exitcode);
	// }
	// close(heredoc.fd);
	// waitpid(heredoc.pid, &heredoc.wstatus, 0);
	// heredoc.exitcode = waitpid_status(heredoc.wstatus);
	// ft_putendl_fd("heredoc finish", 2);
	// if (heredoc.exitcode != SUCCESS)
	// 	return (heredoc.exitcode);
	// return (SUCCESS);
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


