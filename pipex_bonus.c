/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/27 19:39:18 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.i = 0;
	data.argc = argc;
	if (argc >= 5)
	{
		if (check_heredoc(&data.outfile, &data.i, argv, argc) == -1)
			return (FAILED);
		while (data.i <= (argc - 2))
		{
			childprocess(argv[data.i], env, &data);
			data.i++;
		}
	}
	else
	{
		system("leaks pipex");
		return (error_syntax(0));
	}
	system("leaks pipex");
	return (0);
}
