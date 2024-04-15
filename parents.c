/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:09:52 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/14 22:13:45 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parentsprocess(t_data *data, t_fork **p)
{
	while (data->n < (*p)->cmdscount)
	{
		waitpid((*p)->pid[data->n], &(*p)->wstatus, 0);
		(*p)->exitcode = waitpid_status((*p)->wstatus);
		if (data->n == ((*p)->cmdscount) - 1)
			close((*p)->fd[(data->n) - 1][WRITE]);
		else if (data->n == 0)
		{
			if (data->checkheredoc == 1)
				close(data->infile);
			close((*p)->fd[data->n][READ]);
		}
		else
		{
			close((*p)->fd[(data->n) - 1][WRITE]);
			close((*p)->fd[data->n][READ]);
		}
		data->n ++;
	}
	if (data->i == (*p)->cmdscount - 1)
		data->n = -1;
	if ((*p)->exitcode != SUCCESS)
		return ((*p)->exitcode);
	return (SUCCESS);
}
