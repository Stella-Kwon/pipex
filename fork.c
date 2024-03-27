/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:15:57 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/27 19:42:15 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	split_cmd_error(char	***split_cmd)
{
	if (!*split_cmd || !(*split_cmd)[0])
	{
		errors("bash", 1, "", "command not found");
		if (*split_cmd)
			all_free(split_cmd);
		return (FAILED);
	}
	if ((*split_cmd)[0][0] == '.')
	{
		if (access((*split_cmd)[0], X_OK) == -1)
			errors("bash", 1, (*split_cmd)[0], "permission denied");
		else
			errors("bash", 1, (*split_cmd)[0], "is a directory");
		all_free(split_cmd);
		return (FAILED);
	}
	if ((*split_cmd)[0][0] == '/' && access((*split_cmd)[0], X_OK) == -1)
	{
		errors("bash", 1, (*split_cmd)[0], "No such file or directory");
		all_free(split_cmd);
		return (FAILED);
	}
	return (SUCCESS);
}

int	top_execution(char *argv, char **env, char **path, char	***split_cmd)
{
	if (argv[0] == '\0')
	{
		errors("bash", 1, argv, "permission denied");
		return (FAILED);
	}
	*split_cmd = ft_split(argv, ' ');
	if (split_cmd_error(split_cmd) == -1)
		return (FAILED);
	*path = find_path(env);
	if (!(*path) && access((*split_cmd)[0], X_OK) == -1)
	{
		errors("bash", 1, (*split_cmd)[0], "command not found");
		all_free(split_cmd);
		return (FAILED);
	}
	return (SUCCESS);
}

void	execution(char *argv, char **env)
{
	char	*path;
	char	*cmd_path;
	char	**split_cmd;

	split_cmd = NULL;
	cmd_path = NULL;
	path = NULL;
	if (top_execution(argv, env, &path, &split_cmd) == FAILED)
		exit(FAILED);
	cmd_path = find_right_path(argv, &path, &split_cmd);
	if (execve(cmd_path, split_cmd, (char *const *)env) == -1)
	{
		errors("bash", 1, (split_cmd)[0], "command not found");
		if (split_cmd)
			all_free(&split_cmd);
		free_one(&cmd_path);
		exit(FAILED);
	}
}

void	child_childprocess(char *argv, char **env, int *fd, t_data *data)
{
	if (data->i == (data->argc - 2))
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			errors("oufile->dup2", 0, NULL, NULL);
		close(data->outfile);
	}
	else
	{
		close((fd)[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			errors("childprocess_dup2", 0, NULL, NULL);
		close((fd)[1]);
	}
	execution(argv, env);
}

void	childprocess(char *argv, char **env, t_data *data)
{
	int	fd[2];
	int	pid;
	int	wstatus;

	wstatus = -1;
	if (pipe(fd) == -1)
		errors("childprocess_pipe", 0, NULL, NULL);
	pid = fork();
	if (pid == -1)
		errors("childprocess_pid", 0, NULL, NULL);
	if (pid == 0)
		child_childprocess(argv, env, fd, data);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			errors("parentsprocess_dup2", 0, NULL, NULL);
		close(fd[0]);
		wait(&wstatus);
	}
	waitpid_status(wstatus);
}
