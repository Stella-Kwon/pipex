/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/13 00:21:37 by suminkwon        ###   ########.fr       */
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
            // if (argc < 2)
            /*
            argc < 2 경우에는 dup2(fd[0], STDIN_FILENO)와 dup2(fd[1], STDOUT_FILENO)를 사용하여 파이프를 통해 표준 입력과 표준 출력을 연결하는 것은
            이미 프로세스 안에서 stdin과 stdout을 각각 fd[0]과 fd[1]에 연결했기 때문에 에러가 발생합니다.
                %파이프를 생성하고 파일 디스크립터를 사용하는 경우, 보통 파이프의 입출력을 위해 두 개의 파일 디스크립터가 필요하며, 이를 위해 일반적으로 fd[2] 배열을 사용합니다.
                fd[0]은 파이프의 읽기 측을 나타내고, fd[1]은 파이프의 쓰기 측을 나타냅니다.
            따라서 코드에서 fd[0]과 fd[1]을 파이프의 파일 디스크립터로 사용하는 경우, 보통 파이프로 간주됩니다.
            즉, 이미 파일 디스크립터 fd[0]과 fd[1]은 파이프로 연결되어 있기 때문에 다시 연결할 필요가 없습니다.
            이로 인해 dup2() 호출이 실패하고 "Bad file descriptor" 오류가 발생하는 것입니다.
            */
            // {
            //     if (dup2(fd[0], STDIN_FILENO) == -1) // 로 결국 infile을 받고
            //     {
            //         perror("dup2 fd[0]");
            //         close(fd[0]);
            //         close(fd[1]);
            //         return (1);
            //     }
            //     if (dup2(fd[1], STDOUT_FILENO) == -1)
            //     {
            //         perror("dup2 fd[1]");
            //         close(fd[1]);
            //         close(fd[0]);
            //         return (1);
            //     }
            //     while (bytes_read == read(fd[0], buffer, buffersize) > 0)
            //     {
            //         if (write(fd[1], buffer, bytes_read) == -1)
            //         {
            //             close(fd[0]);
            //             close(fd[1]);
            //             perror("read ");
            //             return (1);
            //         }
            //     }
            //     if (bytes_read == -1)
            //     {
            //         close(fd[0]);
            //         close(fd[1]);
            //         perror("read ");
            //         return (1);
            //     }
            //     return (0);
            // }
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
            t_main.pid = fork();
            if (t_main.pid == -1)
            {
                perror("fork ");
                return (1);
            }
            while (argc > 0)
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
                    // bytes_read = 1;
                    // while (bytes_read && !ft_strchr(passage_read, '\0'))
                    // {
                    //     read_buffer = (char *)malloc(BUFFER_S + 1);
                    //     if (!read_buffer)
                    //     {
                    //         free_one(&passage_read);
                    //         return (1);
                    //     }
                    //     bytes_read = read(fd[0], read_buffer, BUFFER_S);
                    //     if (bytes_read == -1)
                    //     {
                    //         perror("read error ");
                    //         close(fd[0]);
                    //         free_both(&passage_read, &read_buffer);
                    //         return (1);
                    //     }
                    //     read_buffer[bytes_read] = '\0';
                    //     passage_read = ft_strjoin_gnl(passage_read, read_buffer);
                    //     read_buffer = free_one(&read_buffer);
                    // }
                    // while ((bytes_read = read(file_fd, read->buffer, BUFFER_SIZE)) > 0)
                    //     bytes_read += bytes_read;
                    // if (bytes_read == -1)
                    // {
                    //     perror("read error ");
                    //     close(fd[0]);
                    //     return (1);
                    // }

                        // execve();

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
