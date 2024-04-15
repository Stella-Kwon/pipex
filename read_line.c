/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:25:21 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 14:43:06 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_charjoin(char **line, t_line *readline)
{
	char	*join;

	join = NULL;
	(*line)[readline->i] = readline->c;
	readline->r_byte = read(STDIN_FILENO, &readline->c, 1);
	if (readline->r_byte == -1)
		return (FAILED);
	readline->i++;
	if (readline->i == readline->buf_size)
	{
		readline->buf_size *= 2;
		// ft_putnbr_fd(readline->buf_size,2);
		// ft_putstr_fd("\n", 2);
		join = (char *)ft_calloc(readline->buf_size, 1);
		if (!(join))
			return (FAILED);
		ft_strlcpy(join, *line, readline->buf_size);
		free(*line); 
		*line = join;
	}
	return (SUCCESS);
}

int	read_line(char **line)
{
	t_line	readline;

	readline.buf_size = 10;
	*line = (char *)ft_calloc(readline.buf_size, 1);
	if (!(*line))
		return (FAILED);
	readline.r_byte = read(STDIN_FILENO, &readline.c, 1);
	if (readline.r_byte == -1)
		return (FAILED);
	readline.i = 0;
	// while (readline.r_byte && ((readline.c != '\0' && readline.c != '\n')))
		while (readline.r_byte && readline.c != '\n')
		{
			if (ft_charjoin(line, &readline) == -1)
				return (FAILED);
	}
	// if (readline.c == '\n')
	// 	(*line)[readline.i] = readline.c;
	// (*line)[++(readline.i)] = '\0';
	return (SUCCESS);
}
