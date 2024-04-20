/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:18 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 22:17:48 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_one(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

int	ft_strcmp(const char *line, const char *limiter)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(limiter);
	if ((ft_strlen(line)) != n)
		return (-1);
	while (i < n && (line[i] != '\0' || limiter[i] != '\0'))
	{
		if ((unsigned char)limiter[i] != (unsigned char)line[i])
			return (-2);
		i++;
	}
	return (0);
}

int	heredoc_child(int fd, char *limiter)
{
	char	*line;

	line = NULL;
	while (read_line(&line) != FAILED)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			line = ft_strjoin(line, "\n");
			if (!line)
				return (errors("read-line ft_strjoin error", 0, NULL, NULL));
			else
				free(line);
			close(fd);
			return (SUCCESS);
		}
		line = ft_strjoin(line, "\n");
		// dprintf(2, "line:%s\n", line); 
		if (write(fd, line, ft_strlen(line)) == -1)
			errors("write", 0, NULL, NULL);
		// if (write(fd, "\n\0", 2) == -1) // this has a problem to read from grep function 
		// 	errors("write", 0, NULL, NULL);
		free(line);
		line = NULL; // 이렇게 안하면 쓰레기 갑이 들어감.
		ft_putstr_fd("> ", 0);
	}
	return (FAILED);
}

/*
즉 /0을 write에다 쓰면 이상한 바이너리가 써진다. cat -e로 보임
정확히 말씀드리자면, write 함수의 세 번째 매개변수로 전달되는 문자열의 길이를 나타내는 값이 \0을 포함해서는 안 됩니다. 
write 함수는 문자열의 길이를 정확히 알아야 하기 때문에, 문자열의 끝을 표시하는 널 종료 문자(\0)를 길이에 포함시키면 안 됩니다.

일반적으로 C 스트링은 널 종료 문자(\0)를 포함하여 문자열의 끝을 나타내지만, write 함수는 명시적으로 문자열의 길이를 지정해주어야 합니다. 
따라서 write 함수에 전달되는 문자열은 널 종료 문자(\0)를 포함시키지 않고, 단순히 문자열의 길이만큼 전달해야 합니다.

따라서 write 함수를 사용할 때는 일반적으로 널 종료 문자(\0)를 포함시키지 않는 것이 좋습니다. 만약 \0을 포함시키면, 해당 문자열 이후의 데이터는 무시되거나 잘못된 결과가 발생할 수 있습니다.
*/
int	here_doc(char *limiter, t_data *data)
{
	t_doc heredoc;

	heredoc.wstatus = -1;
	if (data->argc < 6)
		return (error_syntax(1));
	// heredoc.fd = open_file("tmp", 3, 1);
	// heredoc.fd = open_file(".tmp", 1, 0);
	// if (heredoc.fd == -1)
		// return (FAILED);
	data->infile = open_file(".tmp", 1, 0); // 다르게 줘도 리드모드가 계속 살아있는걸로나와서..
	if (data->infile == -1)
		return (FAILED);
	// heredoc.pid = fork();
	// if (heredoc.pid == -1)
	// 	return (errors("heredoc.pid", 0, NULL, NULL));
	// if (heredoc.pid == 0)
	// {
		ft_putstr_fd("> ", 0);
		heredoc.exitcode = heredoc_child(data->infile, limiter);
		// data->infile = heredoc.fd;
		// close(heredoc.fd);
		// ft_putstr_fd("data->infile :",2);
		// ft_putnbr_fd(data->infile, 2);
		// 	ft_putstr_fd("heredoc.fd :",2);
		// ft_putnbr_fd(heredoc.fd, 2);

		//////////////
		close(data->infile); // Close the file descriptor for write "tmp"
		// getchar();
		data->infile = open_file(".tmp", 0, 0);
		if (data->infile == -1)
			return (FAILED);

		// heredoc.fd = open_file(".tmp", 0, 0);
		// if (heredoc.fd == -1)
		// 	return (FAILED);
		// if (dup2(heredoc.fd, STDIN_FILENO) == -1)
		// 	return (errors("heredoc_dup2", 0, NULL, NULL)); 
		// data->infile = heredoc.fd;
		// close(heredoc.fd);
		// if (unlink("tmp") == -1) 
		// 	return (errors("Failed to unlink file", 0, NULL, NULL));
	return (heredoc.exitcode);
	// }
	// close(heredoc.fd);
	// waitpid(heredoc.pid, &heredoc.wstatus, 0);
	// heredoc.exitcode = waitpid_status(heredoc.wstatus);
	// ft_putendl_fd("heredoc finish", 2);
	// if (heredoc.exitcode != SUCCESS)
	// 	return (heredoc.exitcode);
	// return (SUCCESS);
}

int	check_heredoc(t_data *data)
{
	if (ft_strcmp(data->argv[1], "here_doc") == 0)
	{
		if (here_doc(data->argv[2], data) != SUCCESS)
			return (FAILED);
		data->start = 3;
		data->checkheredoc = 1;
	}
	else
		data->start = 2;
	return (SUCCESS);
}


