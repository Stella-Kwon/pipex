/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/13 16:09:25 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//먼저 argv[1]로 들어오는 파일을 dup2하고 stdin으로
//그후에 fork()를 통해서 자식프로세스를 만들고
// 자식은 무조건 실행하여 dup2로 write하니까 fd[1]를 stdout으로 만든다.
//반대로 그 나눠준 자식의 else인 부모에 끝난 자식의 결과를 읽어드려야 하니까 dup2로 read니까 fd[0]로해서 stdin해준다.
//그리고 그안에 waitpid도해주면서 waitpid종료잘됐는지도 확인하고 
// dup2로 outfile을 없으면 생성해서 만들어주고 stdout으로 바꿔준다.

//여기서 나중의 heredoc할떄도 기억해야 하는게 fork해서 자식에는 한줄씩 읽게해서 read(0, &c, 1) stdin에서 하나하나읽어들여 \0 \n인지 확인하고 
//그 한줄한줄 보면서 limiter과 비교하고 아니면 직접 write(fd[1], ,)해주기
// 그리고 else부모에는 close(fd[1]) 해주고 dup2(fd[0], stdin_filno)하고 waitpid해주기

// 깔끔하게 정리하기


int main(int argc, char **argv, char **env)
{
    t_path *path_data;
    t_main file;
    int statuscode;
    
    // t_read read_var;


    if (argc == 5)
    {
            path_data = new_struct(env);
            if (pipe(fd) == -1)
            {
                perror("Failed to generate pipe");
                return (1);
            }
            if (split_path(&path_data) == -1)
                return (1);
            if (split_argv(argv + 1, &path_data, argc) == -1)
                return (1);
            if (check_wholepath_argv(&path_data) == -1)
                return (1);
            t_main.pid = fork();//첫번째 하고나서 하려했는데 그냥 
            if (t_main.pid == -1)
            {
                perror("fork ");
                return (1);
            }
            while (argc-3 > 0)
            {
                if (t_main.pid == 0)
                {
                    // printf("child id : %d\n", getpid());
                    t_main.infile = open(argv[1], O_RDONLY);
                    if (dup2(t_main.infile, STDIN_FILENO) == -1)
                    {
                        perror("dup2 ");
                        close(t_main.fd[0]);
                        return (1);
                    }


                    close(t_main.fd[0]);
                    }
                    else // if (t_main.pid != 0)
                    {
                        // t_main.pid = fork();
                        // printf("parents id : %d\n", getpid());
                        close(t_main.fd[0]);
                        if (dup2(t_main.fd[1], STDOUT_FILENO) == -1)
                        {
                            perror("dup2 ");
                            close(t_main.fd[1]);
                            return (1);
                        }
                        if (write(t_main.fd[1], passage_read, ft_strlen(passage_read) + 1) == -1)
                        {
                            close(fd[1]);
                            perror("write error ");
                            return (1);
                        }
                        if (argc != 1)
                            close(fd[1]);
                        while (waitpid(pid, &statuscode, WNOHANG) == 0)
                        {
                            printf("child is still processing\n");
                            sleep(1);
                        }
                }
                argc--;
            }
            if (WIFEXITED(statuscode))
            {
                statuscode = WEXITSTATUS(statuscode);
                if (statuscode == 0)
                    printf("Successful\n");
                else
                    printf("Failure with status code %d\n", statuscode);
                    perror("failed exit : ");
                    return (1);
            }
            else if (WIFSIGNALED(statuscode))
            {
                statuscode = WTERMSIG(statuscode);
                printf("Child process terminated due to signal %d\n", statuscode);
                perror("signal error ");
                return (1);
            }
    }  
    else
    {
        ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
        ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
    }
    return (0);
}
