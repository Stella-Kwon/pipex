/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:26:28 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/28 15:31:44 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	path = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][0] == 'P' && env[i][1] == 'A' && \
			env[i][2] == 'T' && env[i][3] == 'H')
			{
				path = env[i];
				return (ft_strdup(path + 5));
			}
			j++;
		}
		i++;
	}
	return (path);
}

void	free_one(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*find_right_path(char *argv, char **path, char ***split_cmd)
{
	t_path	s_p;

	s_p.split_path = ft_split_add_slush(*path, ':');
	s_p.i = 0;
	if (access(*split_cmd[0], X_OK) == 0)
		return (ft_strdup(*split_cmd[0]));
	else if (argv[0] != '/' && access(*split_cmd[0], X_OK) == -1)
	{
		while (s_p.split_path[s_p.i])
		{
			s_p.tmp = ft_strjoin(s_p.split_path[s_p.i], *split_cmd[0]);
			if (access(s_p.tmp, X_OK) == 0)
			{
				all_free(&s_p.split_path);
				return (s_p.tmp);
			}
			s_p.i++;
			free_one(&s_p.tmp);
		}
	}
	if (s_p.split_path)
		all_free(&s_p.split_path);
	return (NULL);
}
