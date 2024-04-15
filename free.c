/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:56:53 by sukwon            #+#    #+#             */
/*   Updated: 2024/04/14 15:57:45 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**all_free(char ***res)
{
	int	i;

	i = 0;
	while ((*res)[i])
	{
		free((*res)[i]);
		(*res)[i] = NULL;
		i++;
	}
	free(*res);
	*res = NULL;
	return (NULL);
}

char	**all_free_int(int ***res, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free((*res)[i]);
		(*res)[i] = NULL;
		i++;
	}
	free(*res);
	*res = NULL;
	return (NULL);
}

void	free_one(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
