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
		line = ft_strjoin(line, "\n\0");
		// dprintf(2, "line:%s\n", line); 
		if (write(fd, line, ft_strlen(line)) == -1)
			errors("write", 0, NULL, NULL);
		// if (write(fd, "\0\n", 2) == -1) // this has a problem to read from grep function 
		// 	errors("write", 0, NULL, NULL);
		free(line);
		line = NULL; // 이렇게 안하면 쓰레기 갑이 들어감.
		ft_putstr_fd("> ", 0);
	}
	return (FAILED);
}
/*
Yes, writing directly to a file descriptor using write() with characters like \0 (null character) and \n (newline character) can still result in the file being treated as binary, 
even though these characters are part of the ASCII table. The key factor here is not the characters themselves but how they are used and interpreted by the tools that read the file.

The ASCII table includes both printable characters (like letters, numbers, and punctuation) and control characters (like \0 and \n). 
While \0 and \n are indeed part of the ASCII table, their presence in a file can lead to the file being interpreted as binary by some tools, such as grep, 
if those tools use heuristics to determine the file type.

grep, for example, might interpret a file as binary if it contains non-printable ASCII characters or if the file does not conform to the expected text file format. 
This is because grep and similar tools often check the first few bytes of a file to determine if it contains binary data. If they find any non-text characters, 
they might assume the file is binary and not process it as text 5.

Even though \0 and \n are part of the ASCII table and are commonly used in text files, 
their presence in a file does not guarantee that the file will be treated as text by all tools. 
The interpretation of a file as text or binary is determined by the file's content and how it is processed by the reading tool.
If a file contains only ASCII characters but is not formatted as a standard text file (e.g., missing a final newline character, 
using non-standard line endings, or containing binary data), it might still be interpreted as binary by some tools 5.

In summary, while \0 and \n are part of the ASCII table and are used in text files, 
the presence of these characters in a file does not guarantee that the file will be treated as text by all tools.
The file's interpretation as text or binary depends on its content and how it is processed by the reading tool.

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


