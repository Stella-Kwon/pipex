/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/15 10:38:36 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	pipex_process(char **argv, t_data *data, t_fork	**p, char **env)
{
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

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	data;
// 	t_fork	*p;

// 	initialize_data(&data, argc, argv);
// 	if (argc >= 5)
// 	{
// 		if (check_heredoc(&data) != SUCCESS)
// 			return (FAILED);
// 		initialize_pipe(&p, data);
// 		while (data.i < (p)->cmdscount)
// 		{
// 			data.childstatus = childprocess(argv[data.start], env, &data, &p);
// 			if (data.childstatus != SUCCESS)
// 				return (data.childstatus);
// 			data.i++;
// 			data.start++;
// 		}
// 		data.childstatus = parentsprocess(&data, &p);
// 		if (data.n == -1)
// 			free_pipe(&p);
// 		if (data.childstatus != SUCCESS)
// 			return (data.childstatus);
// 	}
// 	else
// 		return (error_syntax(1));
// 	return (0);
// }
