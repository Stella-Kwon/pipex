/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:31:11 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/28 15:31:17 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		infile;

	data.i = 0;
	data.argc = argc;
	if (argc == 5)
	{
		infile = open_file(argv[1], 0, 0);
		data.outfile = open_file(argv[argc - 1], 1, 0);
		if (infile == -1 || data.outfile == -1)
			return (FAILED);
		if (dup2(infile, STDIN_FILENO) == -1)
			errors("infile->dup2", 0, NULL, NULL);
		close(infile);
		data.i = 2;
		while (data.i <= (argc - 2))
		{
			childprocess(argv[data.i], env, &data);
			data.i++;
		}
	}
	else
		return (error_syntax(2));
	return (0);
}
