/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/14 21:53:06 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data data;
	t_fork	*p;
	
	// (void)env;
	// getchar();
	initialize_data(&data, argc, argv);
	if (argc >= 5)
	{
		if (check_heredoc(&data) != SUCCESS)
			return (FAILED);
		initialize_pipe(&p, data);
		while (data.i < (p)->cmdscount) // 왜냐면 fork하기전으로 부모는 돌아온다... 그렇기에 똑같이 execution이 
		{
			data.childstatus = childprocess(argv[data.start], env, &data, &p);
			if (data.childstatus != SUCCESS)
				return (data.childstatus);
			// ft_putstr_fd("exit : ", 2);
			// ft_putnbr_fd(data.childstatus, 2);
			// ft_putchar_fd('\n', 2);
			data.i++;
			data.start++;
		}
		data.childstatus = parentsprocess(&data, &p);
		if (data.n == -1)
			free_pipe(&p);
		// while(1);
		if (data.childstatus != SUCCESS)
			return (data.childstatus);
	}
	else
		return (error_syntax(1));
	return (0);
}
