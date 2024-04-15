/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:37:30 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 20:59:28 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **all_free(char ***res)
{
	int i;

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

char **all_free_int(int ***res, int n)
{
	int i;

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

int errors(char *prefix, int n, char *file, char *extra)
{
	if (n == 0)
	{
		prefix = ft_strjoin(prefix, extra);
		if (!prefix)
			ft_putstr_fd("ft_strjoin error in errors()\n", 2);
		else
			perror(prefix);
	}
	if (n == 1)
	{
		// 한줄로 바로 나가게 만드는게 낫기도함.
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(extra, 2);
		ft_putstr_fd("\n", 2);
	}
	return (FAILED);
}

int error_syntax(int heredoc)
{
	ft_putstr_fd("\033[31mError: Syntax is wrong\n\e[0m", 2);
	if (heredoc == 1)
		ft_putstr_fd("\033[36mEx: ./pipex \"here_doc\" \
		<LIMITER> <cmd> <cmd1> <...> <file>\n\e[0m",
					 1);
	else if (heredoc == 0)
		ft_putstr_fd("\033[36mEx: ./pipex <file1> \
		<cmd1> <cmd2> <...> <file2>\n\e[0m",
					 1);
	else if (heredoc == 2)
		ft_putstr_fd("\033[36mEx: ./pipex <file1> \
		<cmd1> <cmd2> <file2>\n\e[0m",
					 1);
	return (FAILED);
}

int open_file(char *file, int fileno, int heredoc)
{
	int open_fd;

	open_fd = 0;
	if (fileno == 0 && heredoc == 0)
		open_fd = open(file, O_RDONLY);
	// else if (fileno == 3 && heredoc == 1)
		// open_fd = open("tmp", O_RDWR | O_CREAT, 0644);
	else if (fileno == 1 && heredoc == 0)
		open_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//| S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH => 텍스트 쓰게 보장해준데서 했는데도 안됌.
	if (open_fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		errors(file, 0, NULL, NULL);
		return (-1);
	}
	return (open_fd);
}

int waitpid_status(int wstatus)
{

	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) == 0)
			return (SUCCESS);
		else
		{ /*
		 WIFEXITED가 true이지만 WEXITSTATUS가 0이 아닐 때는 자식 프로세스가 정상적으로 종료되었지만 종료 코드가 0이 아닌 경우입니다.
		이것은 자식 프로세스가 어떤 이유로 실행이 성공적으로 완료되었지만 특정 문제가 발생했다는 것을 의미합니다.
		이 경우에는 자식 프로세스의 종료 코드를 반환하여 부모 프로세스가 적절한 조치를 취하도록 합니다.
		종료 코드가 0이 아닌 경우, 프로세스가 성공적으로 완료되었지만 일부 작업 또는 조건에 문제가 있을 수 있음을 나타냅니다.
		 이러한 상황에 따라 부모 프로세스는 추가적인 오류 처리 또는 로깅을 수행할 수 있습니다.
		 */
			// errors("WAIT_STATUS", 1, \
			// "Child process terminated but there is some error in running time", \
			// ft_itoa(WEXITSTATUS(wstatus)));
			return (WEXITSTATUS(wstatus));
		}
	}
	else if (WIFSIGNALED(wstatus))
	{
		errors("WAIT_STATUS", 1,
			   "Child process terminated due to signal",
			   ft_itoa(WTERMSIG(wstatus)));
		return (WTERMSIG(wstatus));
	}
	else if (WIFSTOPPED(wstatus))
	{
		errors("WAIT_STATUS", 1,
			   "Child process was stopped by signal", ft_itoa(WSTOPSIG(wstatus)));
		return (WSTOPSIG(wstatus));
	}
	ft_putstr_fd("Unexpected termination status\n", 2);
	return (FAILED);
}