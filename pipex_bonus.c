/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/15 20:13:55 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	pipex_process(char **argv, t_data *data, t_fork	**p, char **env)
{
	int	tmp;

	tmp = data->i;
	while (tmp < (*p)->cmdscount - 1)
	{
		if (pipe((*p)->fd[tmp]) == -1)
			return (errors("childprocess : pipe failed", 0, NULL, NULL));
		tmp++;
	}
	while (data->i < (*p)->cmdscount)
	{
		data->childstatus = childprocess(argv[data->start], env, data, p);
		if (data->childstatus != SUCCESS)
			return (data->childstatus);
		data->i++;
		data->start++;
	}
	data->childstatus = parentsprocess(data, p);
	if (data->n == -1)
		free_pipe(p);
	if (data->childstatus != SUCCESS)
		return (data->childstatus);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_fork	*p;

	initialize_data(&data, argc, argv);
	if (argc >= 5)
	{
		if (check_heredoc(&data) != SUCCESS)
			return (FAILED);
		initialize_pipe(&p, data);
		data.childstatus = pipex_process(argv, &data, &p, env);
		if (data.childstatus != SUCCESS)
			return (data.childstatus);
	}
	else
		return (error_syntax(1));
	return (0);
}
