/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:18 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/27 18:42:07 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_child(int (*heredoc_fd)[2], char *limiter)
{
	char	*line;

	line = NULL;
	close((*heredoc_fd)[0]);
	while (read_line(&line) != -1)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			if (line)
				free(line);
			close((*heredoc_fd)[1]);
			exit(SUCCESS);
		}
		if (write((*heredoc_fd)[1], line, ft_strlen(line) + 1) == -1)
			errors("write", 0, NULL, NULL);
		free(line);
		line = NULL;
	}
}

void	here_doc(int argc, char *limiter)
{
	int		heredoc_fd[2];
	pid_t	heredoc_pid;
	int		wstatus;

	wstatus = -1;
	if (argc < 6)
		error_syntax(1);
	if (pipe(heredoc_fd) == -1)
		errors("pipe", 0, NULL, NULL);
	heredoc_pid = fork();
	if (heredoc_pid == -1)
		errors("heredoc_pid", 0, NULL, NULL);
	if (heredoc_pid == 0)
		heredoc_child(&heredoc_fd, limiter);
	else
	{
		close(heredoc_fd[1]);
		if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
			errors("heredoc_dup2", 0, NULL, NULL);
		close(heredoc_fd[0]);
		waitpid(heredoc_pid, &wstatus, 0);
	}
	waitpid_status(wstatus);
}

int	not_heredoc(int *outfile, char **argv, int argc)
{
	int	infile;

	infile = open_file(argv[1], 0, 0);
	*outfile = open_file(argv[argc - 1], 1, 0);
	if (infile == -1 || *outfile == -1)
		return (FAILED);
	if (dup2(infile, STDIN_FILENO) == -1)
		errors("infile->dup2", 0, NULL, NULL);
	close(infile);
	return (SUCCESS);
}

int	check_heredoc(int *outfile, int *i, char **argv, int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		*outfile = open_file(argv[argc - 1], 1, 1);
		here_doc(argc, argv[2]);
		*i = 3;
	}
	else
	{
		if (not_heredoc(outfile, argv, argc) == FAILED)
			return (FAILED);
		*i = 2;
	}
	return (SUCCESS);
}
