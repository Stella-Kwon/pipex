/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:21:52 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 16:15:33 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_cmdscount(t_fork **p, t_data data)
{
	(*p)->cmdscount = 0;
	while (data.start <= (data.argc - 2))
	{
		(*p)->cmdscount++;
		data.start++;
	}
	return ((*p)->cmdscount);
}

void	initialize_pipe(t_fork **p, t_data data)
{
	int	i;

	*p = (t_fork *)malloc(sizeof(t_fork));
	if (!(*p))
		errors("struct malloc error : initialize_p\n", 0, NULL, NULL);
	(*p)->cmdscount = find_cmdscount(p, data);
	(*p)->fd = (int **)malloc(sizeof(int *) * ((*p)->cmdscount - 1));
	if (!(*p)->fd)
		errors("**fd malloc error : initialize_p\n", 0, NULL, NULL);
	i = 0;
	while (i < (*p)->cmdscount - 1)
	{
		(*p)->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(*p)->fd[i])
			errors("*fd malloc error : initialize_p\n", 0, NULL, NULL);
		i++;
	}
	(*p)->pid = (pid_t *)malloc(sizeof(pid_t) * (*p)->cmdscount);
	if (!(*p)->pid)
		errors("pid malloc error : initialize_p\n", 0, NULL, NULL);
	(*p)->wstatus = 0;
	(*p)->exitcode = -1;
}

void	initialize_data(t_data	*data, int argc, char **argv)
{
	data->i = 0;
	data->start = 0;
	data->argc = argc;
	data->childstatus = 0;
	data->argv = argv;
	data->checkheredoc = 0;
	data->n = 0;
	data->infile = -1;
	data->outfile = -1;
}

void	free_pipe(t_fork **pipe)
{
	all_free_int(&(*pipe)->fd, ((*pipe)->cmdscount - 1));
	free((*pipe)->pid);
	(*pipe)->pid = NULL;
	free(*pipe);
	*pipe = NULL;
}
