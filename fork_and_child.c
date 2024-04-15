/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:15:57 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/15 14:12:13 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	last_cmd_action(t_fork **p, t_data *data)
{
	data->outfile = open_file(data->argv[data->argc - 1], 1, 0);
	if (data->outfile == -1)
		return (FAILED);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		return (errors("outfile->dup2", 0, NULL, NULL));
	close(data->outfile);
	close((*p)->fd[(data->i) - 1][WRITE]);
	if (dup2((*p)->fd[(data->i) - 1][READ], STDIN_FILENO) == -1)
		return (errors("last_cmd_action : stdin_dup2", 0, NULL, NULL));
	close((*p)->fd[(data->i) - 1][READ]);
	return (SUCCESS);
}

int	first_cmd_action(t_fork **p, t_data *data)
{
	if (data->checkheredoc == 0 && data->start == 2)
	{
		data->infile = open_file(data->argv[1], 0, 0);
		if (data->infile == -1)
			return (FAILED);
	}
	if (dup2(data->infile, STDIN_FILENO) == -1)
		return (errors("infile->dup2", 0, NULL, NULL));
	close(data->infile);
	if (data->checkheredoc == 1)
	{
		if (unlink(".tmp") == -1)
			return (errors("Failed to unlink file", 0, NULL, NULL));
	}
	close((*p)->fd[data->i][READ]);
	if (dup2((*p)->fd[data->i][WRITE], STDOUT_FILENO) == -1)
		return (errors("first_cmd_action: stdout_dup2", 0, NULL, NULL));
	close((*p)->fd[data->i][WRITE]);
	return (SUCCESS);
}

int	cmds_action(t_fork **p, t_data *data)
{
	close((*p)->fd[(data->i) - 1][WRITE]);
	if (dup2((*p)->fd[(data->i) - 1][READ], STDIN_FILENO) == -1)
		return (errors("cmds_action : stdin_dup2", 0, NULL, NULL));
	close((*p)->fd[(data->i) - 1][READ]);
	close((*p)->fd[data->i][READ]);
	if (dup2((*p)->fd[data->i][WRITE], STDOUT_FILENO) == -1)
		return (errors("cmds_action : stdout_dup2", 0, NULL, NULL));
	close((*p)->fd[data->i][WRITE]);
	return (SUCCESS);
}

int	child_childprocess(char *argv, t_fork **p, t_data *data, char **env)
{
	if (data->i == ((*p)->cmdscount) - 1)
	{
		if (last_cmd_action(p, data) == FAILED)
			exit (FAILED);
	}
	else if (data->i == 0)
	{
		if (first_cmd_action(p, data) == FAILED)
			exit(FAILED);
	}
	else
	{
		if (cmds_action(p, data) == FAILED)
			exit(FAILED);
	}
	(*p)->exitcode = execution(argv, env);
	if ((*p)->exitcode != SUCCESS)
		return ((*p)->exitcode);
	return (SUCCESS);
}

int	childprocess(char *argv, char **env, t_data *data, t_fork **p)
{
	if (data->i < (*p)->cmdscount - 1)
	{
		if (pipe((*p)->fd[data->i]) == -1)
			return (errors("childprocess : pipe failed", 0, NULL, NULL));
	}
	(*p)->pid[data->i] = fork();
	if ((*p)->pid[data->i] == -1)
		return (errors("childprocess : fork failed", 0, NULL, NULL));
	if ((*p)->pid[data->i] == 0)
	{
		(*p)->exitcode = child_childprocess(argv, p, data, env);
		exit((*p)->exitcode);
	}
	if (data->i == ((*p)->cmdscount) - 1)
		close((*p)->fd[(data->i) - 1][READ]);
	else if (data->i == 0)
		close((*p)->fd[data->i][WRITE]);
	else
	{
		close((*p)->fd[(data->i) - 1][READ]);
		close((*p)->fd[data->i][WRITE]);
	}
	return (SUCCESS);
}
