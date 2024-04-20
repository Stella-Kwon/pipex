/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:37:30 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/15 18:41:52 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	errors(char *prefix, int n, char *file, char *extra)
{
	if (n == 0)
	{
		prefix = ft_strjoin(prefix, extra);
		if (!prefix)
			ft_putstr_fd("ft_strjoin error in errors()\n", 2);
		else
			perror(prefix);
	}
	if (n == 1)
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(extra, 2);
		ft_putstr_fd("\n", 2);
	}
	return (FAILED);
}

int	error_syntax(int heredoc)
{
	ft_putstr_fd("\033[31mError: Syntax is wrong\n\e[0m", 2);
	if (heredoc == 1)
		ft_putstr_fd("\033[36mEx: ./pipex \"here_doc\" \
		<LIMITER> <cmd> <cmd1> <...> <file>\n\e[0m", 1);
	else if (heredoc == 0)
		ft_putstr_fd("\033[36mEx: ./pipex <file1> \
		<cmd1> <cmd2> <...> <file2>\n\e[0m", 1);
	else if (heredoc == 2)
		ft_putstr_fd("\033[36mEx: ./pipex <file1> \
		<cmd1> <cmd2> <file2>\n\e[0m", 1);
	return (FAILED);
}

int	open_file(char *file, int fileno, int heredoc)
{
	int	open_fd;

	open_fd = 0;
	if (fileno == 0 && heredoc == 0)
		open_fd = open(file, O_RDONLY);
	else if (fileno == 1 && heredoc == 1)
		open_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (fileno == 1 && heredoc == 0)
		open_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (open_fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		errors(file, 0, NULL, NULL);
		return (-1);
	}
	return (open_fd);
}

int	waitpid_status(int wstatus)
{
	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) == 0)
			return (SUCCESS);
		else
			return (WEXITSTATUS(wstatus));
	}
	else if (WIFSIGNALED(wstatus))
	{
		errors("WAIT_STATUS", 1, \
		"Child process terminated due to signal", \
		ft_itoa(WTERMSIG(wstatus)));
		return (WTERMSIG(wstatus));
	}
	else if (WIFSTOPPED(wstatus))
	{
		errors("WAIT_STATUS", 1, \
		"Child process was stopped by signal", ft_itoa(WSTOPSIG(wstatus)));
		return (WSTOPSIG(wstatus));
	}
	ft_putstr_fd("Unexpected termination status\n", 2);
	return (FAILED);
}
