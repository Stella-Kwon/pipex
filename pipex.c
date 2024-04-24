/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:31:11 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/14 16:09:32 by sukwon           ###   ########.fr       */
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
	if (argc == 5)
	{
		data.start = 2;
		initialize_pipe(&p, data);
		data.childstatus = pipex_process(argv, &data, &p, env);
		if (data.childstatus != SUCCESS)
			return (data.childstatus);
	}
	else
		return (error_syntax(0));
	return (0);
}

