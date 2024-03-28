/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:31:11 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/28 10:39:06 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	t_data data;

	data.i = 0;
	data.argc = argc;
	if (argc == 5)
	{
		int infile;
		int outfile;
	
		infile = open_file(argv[1], 0, 0);
		outfile = open_file(argv[argc - 1], 1, 0);
		if (infile == -1 || outfile == -1)
			return (FAILED);
		if (dup2(infile, STDIN_FILENO) == -1)
			errors("infile->dup2", 0, NULL, NULL);
		close(infile);
		while (data.i <= (argc - 2))
		{
			childprocess(argv[data.i], env, &data);
			data.i++;
		}
	}
	else
	{
		system("leaks pipex");
		return (error_syntax(2));
	}
	system("leaks pipex");
	return (0);
}
