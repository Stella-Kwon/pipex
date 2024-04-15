/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:15:57 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 22:17:54 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	last_cmd_action(t_fork **p, t_data *data)
{
	// if (data->checkheredoc == 1)
	// 	data->outfile = open_file(data->argv[data->argc - 1], 1, 1);
	// else
	data->outfile = open_file(data->argv[data->argc - 1], 1, 0);
	if (data->outfile == -1)
		return (FAILED);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		return (errors("outfile->dup2", 0, NULL, NULL));
	close(data->outfile);
	close((*p)->fd[(data->i) - 1][WRITE]); //이미했어 전에 close 하지만 부모에선 안닫혔으니 ㄱㅊ
	if (dup2((*p)->fd[(data->i) - 1][READ], STDIN_FILENO) == -1)
		return (errors("last_cmd_action : stdin_dup2", 0, NULL, NULL));
	close((*p)->fd[(data->i) - 1][READ]);
	return (SUCCESS);
}

int	first_cmd_action(t_fork **p, t_data *data)
{
	if (data->checkheredoc == 0 && data->start == 2)
	{
		// ft_putstr_fd("infile\n",2);
		data->infile = open_file(data->argv[1], 0, 0);
		if (data->infile == -1)
			return (FAILED);
		// ft_putstr_fd("data->infile :",2);
		// ft_putnbr_fd(data->infile, 2);
	}
	// else
	// {
	// 	data->infile = open_file(".tmp", 0, 0);
	// 	if (data->infile == -1)
	// 		return (FAILED);
	// }
	// while(1);
	// ft_putstr_fd("data->infile :",2);
	// ft_putnbr_fd(data->infile, 2);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		return (errors("infile->dup2", 0, NULL, NULL));
	close(data->infile);
	// while(1); // 얘는 나중에 자식프로세스 다끝나고 마지막 waitpid에서 반영되어 중지되지않고 자식프로세스를 기다린다
	// ft_putstr_fd("\n\ngetchar soon \n\n",2);
	// getchar();
	// getchar();
	/*
		네, 일반적으로 자식 프로세스는 부모 프로세스와 병렬로 실행됩니다. 
		따라서 자식 프로세스는 백그라운드에서 실행될 수 있습니다. 
		하지만 이것은 모든 경우에 해당하는 것은 아닙니다.
		 예를 들어, 자식 프로세스가 특정 작업을 수행하기 위해 부모 프로세스로부터 대기 상태에 
		 들어간 경우에는 백그라운드에서 실행되지 않을 수 있습니다.
		따라서 getchar() 함수가 자식 프로세스에서 작동하지 않는다면,
		그 이유는 자식 프로세스가 현재 백그라운드에서 실행 중이거나
		 표준 입력이 제대로 설정되지 않았기 때문일 수 있습니다.
		  종종 자식 프로세스는 백그라운드에서 실행되지만, 
		  그렇지 않은 경우도 있으므로 특정 상황에 따라 달라질 수 있습니다.
	*/
//그래서 여기까지는 .tmp가 살아있고 전달이됐어..
	if (data->checkheredoc == 1)
	{
		if (unlink(".tmp") == -1) 
			return (errors("Failed to unlink file", 0, NULL, NULL));
	}
	// while(1);
	// 밑에서 설명함
	close((*p)->fd[data->i][READ]);
	if (dup2((*p)->fd[data->i][WRITE], STDOUT_FILENO) == -1)
		return (errors("first_cmd_action: stdout_dup2", 0, NULL, NULL));
	close((*p)->fd[data->i][WRITE]);
	return (SUCCESS);
}

// int	heredoc_action(t_fork **p, t_data *data)
// {
// 	if (data->checkheredoc == 1 && data->start == 3)
// 	{
// 		ft_putstr_fd("heredoc\n",2);
// 		if (dup2((*p)->fd[data->i][READ], STDIN_FILENO) == -1)
// 			return (errors("heredoc -> fd[read]", 0, NULL, NULL));
// 		close((*p)->fd[data->i][READ]);
// 	}
// 	// if (dup2((*p)->fd[data->i][WRITE], STDOUT_FILENO) == -1)
// 	// 	return (errors("first_cmd_action: stdout_dup2", 0, NULL, NULL));
// 	// close((*p)->fd[data->i][WRITE]);
// 	return (SUCCESS);
// }

int	cmds_action(t_fork **p, t_data *data)
{
	close((*p)->fd[(data->i) - 1][WRITE]);
	if (dup2((*p)->fd[(data->i) - 1][READ], STDIN_FILENO) == -1)
		return (errors("cmds_action : stdin_dup2", 0, NULL, NULL));
	close((*p)->fd[(data->i) - 1][READ]);
	close((*p)->fd[data->i][READ]);
	if (dup2((*p)->fd[data->i][WRITE], STDOUT_FILENO) == -1)
		return (errors("cmds_action : stdout_dup2", 0, NULL, NULL));
	close((*p)->fd[data->i][WRITE]);
	return (SUCCESS);
}

int	child_childprocess(char *argv, t_fork **p, t_data *data, char **env)
{
	if (data->i == ((*p)->cmdscount) - 1)
	{
		// ft_putendl_fd("last",2);
		if (last_cmd_action(p, data) == FAILED)
			exit (FAILED);
	}
	else if (data->i == 0)
	{
		// ft_putendl_fd("first",2);
		if (first_cmd_action(p, data) == FAILED)
			exit(FAILED);
	}
	else
	{
		// ft_putendl_fd("middle",2);
		if (cmds_action(p, data) == FAILED)
			exit(FAILED);
	}
	// ft_putendl_fd("before execution",2);
	(*p)->exitcode = execution(argv, env);
	if ((*p)->exitcode != SUCCESS)
		return ((*p)->exitcode);
	return (SUCCESS);
}

int	childprocess(char *argv, char **env, t_data *data, t_fork **p)
{
	if (data->i < (*p)->cmdscount - 1)
	{
		// ft_putstr_fd("\n", 2);
		// ft_putstr_fd("pipe :",2);
		// ft_putnbr_fd(data->i,2);
		// ft_putchar_fd('\n',2);
		if (pipe((*p)->fd[data->i]) == -1)
			return (errors("childprocess : pipe failed", 0, NULL, NULL));
	}
	(*p)->pid[data->i] = fork();
	// ft_putstr_fd("fork : ", 2);
	// ft_putnbr_fd((*p)->pid[data->n], 2);
	// ft_putnbr_fd(data->i,2);
	// ft_putstr_fd("\n", 2);
	if ((*p)->pid[data->i] == -1)
		return (errors("childprocess : fork failed", 0, NULL, NULL));
	if ((*p)->pid[data->i] == 0)
	{
		// ft_putstr_fd("cmd :",2);
		// ft_putstr_fd(argv,2);
		// ft_putchar_fd('\n',2);
		// ft_putstr_fd("pid : ", 2);
		// ft_putnbr_fd((*p)->pid[data->n], 2);
		// ft_putchar_fd('\n',2);
		// ft_putstr_fd("in child\n",2);
		(*p)->exitcode = child_childprocess(argv, p, data, env);
		// ft_putstr_fd("exec failed\n",2);
		exit((*p)->exitcode);
	}

	// ft_putstr_fd("in parents 1\n",2);
	// getchar();
	// getchar();
	if (data->i == ((*p)->cmdscount) - 1)
	{
		// ft_putendl_fd("parents last",2);
		close((*p)->fd[(data->i) - 1][READ]);
	}
	else if (data->i == 0)
	{
		// getchar();
		// close(data->infile);
/*
여기에 하면 안되는이유는 fork() 함수가 호출되면, 
부모 프로세스의 상태가 자식 프로세스로 복제됩니다. 
이는 파일 디스크립터도 포함됩니다. 
하지만 fork() 이후에도 파일 디스크립터는 해당 파일에 대한 참조를 유지합니다.
따라서 부모 프로세스에서 파일 디스크립터를 닫은 후에도 
자식 프로세스는 해당 파일에 대한 접근이 가능합니다.

하지만 문제가 발생하는 경우는 부모프로세스에서 파일 디스크립터를 닫은 후에 
자식 프로세스가 해당 파일에 접근할 때입니다.
이때 파일 시스템에서의 해당 파일에 대한 참조가 변경되거나 해제될 수 있습니다. 
이것은 파일 디스크립터를 닫는 시점과 방법에 따라 달라질 수 있습니다.
 즉,
 읽기라던지 쓰기같은 경우는 파일에 대한 참조 위치가 중요한데, (메모리 address) 그것이 해제될수 있기 떄문에,
 읽거나 쓰기전에 close()해버리면 파일디스크립터는 독립적으로 유지되어 존재하지만,
 그 해당 파일에대한 참조를 잃어 더 이상 잃거나 쓸수가 없는 상황이 되어버린다.
 
따라서 파일을 올바르게 다루기 위해서는 파일 디스크립터를 닫는 시점과 방법을 신중하게 고려해야 합니다.
 특히 부모 프로세스와 자식 프로세스 간의 파일 디스크립터 관리는 주의 깊게 처리해야 합니다.
*/
		// ft_putendl_fd("parents first",2);
		close((*p)->fd[data->i][WRITE]);
	}
	else
	{
		// ft_putendl_fd("parents middle",2);
		close((*p)->fd[(data->i) - 1][READ]);
		close((*p)->fd[data->i][WRITE]);
	}
	return (SUCCESS);
}



int	parentsprocess (t_data *data, t_fork **p) //stat -f "%Lp" 파일이름
{
	// ft_putstr_fd("in parents 2\n",2);

	while (data->n < (*p)->cmdscount) // pid
	{
		// ft_putnbr_fd(data->n, 2);
		// ft_putstr_fd("in parents 2\n",2);
		// ft_putnbr_fd((*p)->pid[data->n], 2);
		waitpid((*p)->pid[data->n], &(*p)->wstatus, 0);
		// ft_putstr_fd("pid : ", 2);
		// ft_putnbr_fd(data->n, 2);
		// ft_putstr_fd("\n", 2);
		(*p)->exitcode = waitpid_status((*p)->wstatus);
		if (data->n == ((*p)->cmdscount) - 1)
		{
			// ft_putendl_fd("close last fds parents last",2);
			close((*p)->fd[(data->n) - 1][WRITE]);
		}
		else if (data->n == 0)
		{
			if (data->checkheredoc == 1)
				close(data->infile);
			// ft_putendl_fd("close last fds parents first",2);
			close((*p)->fd[data->n][READ]);
		}
		else
		{
			// ft_putendl_fd("close last fds parents middle",2);
			close((*p)->fd[(data->n) - 1][WRITE]);
			close((*p)->fd[data->n][READ]);
		}
		data->n ++;
	}

	if (data->i == (*p)->cmdscount - 1)
		data->n = -1;
	// ft_putstr_fd("close all pipe after\n",2);
	if ((*p)->exitcode != SUCCESS)
		return ((*p)->exitcode);
	return (SUCCESS);
}
