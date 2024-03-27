/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/27 16:21:37 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// 먼저 argv[1]로 들어오는 파일을 dup2하고 stdin으로
// 그후에 fork()를 통해서 자식프로세스를 만들고
//  자식은 무조건 실행하여 dup2로 write하니까 fd[1]를 stdout으로 만든다.
// 반대로 그 나눠준 자식의 else인 부모에 끝난 자식의 결과를 읽어드려야 하니까 dup2로 read니까 fd[0]로해서 stdin해준다.
// 그리고 그안에 waitpid도해주면서 waitpid종료잘됐는지도 확인하고
//  dup2로 outfile을 없으면 생성해서 만들어주고 stdout으로 바꿔준다.

// 여기서 나중의 heredoc할떄도 기억해야 하는게 fork해서 자식에는 한줄씩 읽게해서 read(0, &c, 1) stdin에서 하나하나읽어들여 \0 \n인지 확인하고
// 그 한줄한줄 보면서 limiter과 비교하고 아니면 직접 write(fd[1], ,)해주기
//  그리고 else부모에는 close(fd[1]) 해주고 dup2(fd[0], stdin_filno)하고 waitpid해주기
// 깔끔하게 정리하기

// int errors(char *prefix)
// {
//     perror(prefix);
//     return (FAILED);
// }
int errors(char *prefix, int n, char *file, char* extra)
{
    if (n == 0)
    {
        ft_putstr_fd(prefix, 2); // zsh
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("command not found: ", 2);
        ft_putstr_fd(file, 2); // cmd
        ft_putstr_fd("\n", 2);
    }
    if (n == 1)
    {
        // ft_putstr_fd(prefix, 2); // 되는 cmd
        // ft_putstr_fd(":", 2);
        perror(prefix);
    }
    if (n == 2)
    {
        ft_putstr_fd(prefix, 2); //
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("permission denied: ", 2);
        ft_putstr_fd(file, 2); // filename
        ft_putstr_fd("\n", 2);
    }
    if (n == 3)
    {
        ft_putstr_fd(prefix, 2); //
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(extra, 2);
        ft_putstr_fd(file, 2); // filename
        ft_putstr_fd("\n", 2);
    }
    return (FAILED);
}

int error_syntax(int heredoc)
{
    ft_putstr_fd("\033[31mError: Syntax is wrong\n\e[0m", 2);
    if (heredoc == 1)
        ft_putstr_fd("\033[34mEx: ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n\e[0m", 1);
    else if (heredoc == 0)
        ft_putstr_fd("\033[32mEx: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n\e[0m", 1);
    return (FAILED);
}

int open_file(char *file, int fileno, int heredoc)
{
    int open_fd;

    open_fd = 0;
    if (fileno == 0 && heredoc == 0)
        open_fd = open(file, O_RDONLY, 0777);
    else if (fileno == 1 && heredoc == 1)
        open_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
    else if (fileno == 1 && heredoc == 0)
        open_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (open_fd == -1)
        return (errors("zsh", 2, file, NULL));
    return (open_fd);
}

int waitpid_status(int wstatus) //, pid_t pid)
{
    if (WIFEXITED(wstatus))
    {
        // printf("\n\nsuccess\n\n");
        return (SUCCESS);
    }
    else if (WIFSIGNALED(wstatus))
    {
        // int signum = WTERMSIG(wstatus);
        // printf("Child process terminated due to signal %d\n", signum);
        // return (errors("waitpid : unexpected teminate "));
        return (FAILED);
    }
    else if (WIFSTOPPED(wstatus)) // where the child process is stopped.
    {
        // int stop = WSTOPSIG(wstatus);
        // printf("Child process was stopped by signal %d\n", stop);
        // return (errors("waitpid : stopped by signal "));
        return (FAILED);
    }
    // printf("Unexpected termination status\n");
    // return (errors("other issue"));
    return (FAILED);
}

int ft_charjoin(char **line, t_line *readline)
{
    char *join;

    join = NULL;
    // printf("line before while : %s\n", *line);
    (*line)[readline->i] = readline->c; //(*line)게 해주는게 중요해-> 메모리에세싱이 잘 안될수 있어 안해주면
    if ((readline->r_byte = read(STDIN_FILENO, &readline->c, 1)) == -1)
        return (FAILED);
    // printf("line in while : %s\n", *line);
    readline->i++;
    // printf("i : %d\n", readline->i);
    if (readline->i == readline->buf_size)
    {
        // printf("buf_size : %d\n", readline->buf_size);
        readline->buf_size *= 2;
        // printf("buf_size : %d\n", readline->buf_size);
        join = (char *)ft_calloc(readline->buf_size, 1);
        if (!(join))
            return (FAILED);
        ft_strlcpy(join, *line, readline->buf_size);
        free(*line);
        *line = join;
    }
    return (SUCCESS);
}

int read_line(char **line) // get_next_line으로 할려다가 많은데이터를 잃는게아니고  \0도 핸들링해야해서 새러 생성
{
    t_line readline;

    readline.buf_size = 10;
    *line = (char *)ft_calloc(readline.buf_size, 1);
    if (!(*line))
        return (FAILED);
    if ((readline.r_byte = read(STDIN_FILENO, &readline.c, 1)) == -1)
        return (FAILED);
    readline.i = 0;
    while (readline.r_byte && ((readline.c != '\0' && readline.c != '\n')))
    {
        if (ft_charjoin(line, &readline) == -1)
            return (FAILED);
    }
    if (readline.c == '\n')
        (*line)[readline.i] = readline.c;
    (*line)[++(readline.i)] = '\0';
    // printf("null\n");
    return (SUCCESS);
}
// void heredoc_child(int *fd, char *limiter)
// {
//     char *line;

//     line = NULL;
//     close(fd[0]);
//     while (read_line(&line) != -1)
//     {

//         // printf("line  : %s\n", line);
//         if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
//         {
//             if (line)
//                 free(line);
//             close(fd[1]); // 어차피 종료되면 알아서 닫히긴함.
//             // printf("here_doc child is successfully finished\n\n");
//             return;
//         }
//         // return 하더라도 부모프로세스로 가지 함수가 호출자 함수가 종료되진않아. 하나의 함수라고 생가가면됨.
//         if (write(fd[1], line, ft_strlen(line) + 1) == -1) // 터미널에 보여줘야하니까
//             errors("write");
//         free(line);
//         line = NULL; // 이거안해주면 계속 쓰레기값들어감
//     }
// }
void heredoc_child(int (*heredoc_fd)[2], char *limiter)
{
    char *line;

    line = NULL;
    close((*heredoc_fd)[0]);
    while (read_line(&line) != -1)
    {

        // printf("line  : %s\n", line);
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
        {
            if (line)
                free(line);
            close((*heredoc_fd)[1]); // 어차피 종료되면 알아서 닫히긴함.
            // printf("here_doc child is successfully finished\n\n");
            // return; // because of this it continues child proccess to be not terminated
            exit(SUCCESS);
        }
        // return 하더라도 부모프로세스로 가지 함수가 호출자 함수가 종료되진않아. 하나의 함수라고 생가가면됨.
        if (write((*heredoc_fd)[1], line, ft_strlen(line) + 1) == -1) // 터미널에 보여줘야하니까
            errors("write", 1, NULL, NULL);
        free(line);
        line = NULL; // 이거안해주면 계속 쓰레기값들어감
    }
}
// void heredoc_parents(int (*fd)[2], int *wstatus, pid_t pid)
// {
//     close((*fd)[1]);
//     if (dup2((*fd)[0], STDIN_FILENO) == -1)
//         errors("dup2 heredoc");
//     // printf("fd[0] : here_doc parents %d\n", (*fd)[0]);
//     close((*fd)[1]);
//     // printf("STDOUT_FILENO : here_doc parents %d\n", STDOUT_FILENO);
//     waitpid(pid, wstatus, WEXITED);
//     // dup2() 함수에 전달된 파일 디스크립터가 표준 입력, 표준 출력, 또는 표준 에러에 대한 파일 디스크립터인 경우에는
//     // 특별한 처리가 필요합니다. 이러한 표준 스트림에 대한 파일 디스크립터는 닫거나 재지정되지 않아야 합니다.
//     //  그렇지 않으면 예기치 않은 동작이 발생할 수 있습니다.
//     // 하지만 여기서는 마지막 단계니까 ㄱㅊ은듯
//     // return;
//     }

// void here_doc(int argc, char *limeter)
// {
//     t_main file;

//     if (argc < 6)
//         error_syntax(1);
//     if (pipe(file.fd) == -1)
//         errors("zsh");
//     file.pid = fork();
//     if (file.pid == -1)
//         errors("zsh");
//     if (file.pid == 0)
//         heredoc_child(file.fd, limeter);
//     else
//     { // heredoc_parents(file.fd, file.wstatus);
//         close(file.fd[1]);
//         if (dup2(file.fd[0], STDIN_FILENO) == -1)
//             errors("zsh");
//         wait(&file.wstatus);
//         close(file.fd[0]); //알아서 종료되면 닫히겠지.
//     }
//     waitpid_status(file.wstatus);
// }

void here_doc(int argc, char *limiter)
{
    int heredoc_fd[2];
    pid_t heredoc_pid;
    int wstatus;

    wstatus = -1;
    if (argc < 6)
        error_syntax(1);
    if (pipe(heredoc_fd) == -1)
        errors("pipe", 1, NULL, NULL);
    // printf("before fork\n");
    heredoc_pid = fork();
    // printf("hi\n");
    if (heredoc_pid == -1)
        errors("heredoc_pid", 1, NULL, NULL);
    if (heredoc_pid == 0)
    {
        // printf("before heredoc_child\n");
        heredoc_child(&heredoc_fd, limiter);
        // char *line;

        // line = NULL;
        // close(heredoc_fd[0]);
        // while (read_line(&line) != -1)
        // {

        //     // printf("line  : %s\n", line);
        //     if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
        //     {
        //         if (line)
        //             free(line);
        //         close(heredoc_fd[1]); // 어차피 종료되면 알아서 닫히긴함.
        //         // printf("here_doc child is successfully finished\n\n");
        //         return ;//because it ends the whole totally
        //     }
        //     // return 하더라도 부모프로세스로 가지 함수가 호출자 함수가 종료되진않아. 하나의 함수라고 생가가면됨.
        //     if (write(heredoc_fd[1], line, ft_strlen(line) + 1) == -1) // 터미널에 보여줘야하니까
        //         errors("write");
        //     free(line);
        //     line = NULL; // 이거안해주면 계속 쓰레기값들어감
        // }
        // printf("should not printed\n");
    }
    else
    {
        // printf("before heredoc_parents\n");
        // heredoc_parents(&(heredoc_fd), &wstatus, pid);
        close(heredoc_fd[1]);
        if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
            errors("heredoc_dup2", 1, NULL, NULL);
        // printf("heredoc_fd[0] : here_doc parents %d\n", heredoc_fd[0]);
        close(heredoc_fd[0]);
        // printf("STDOUT_FILENO : here_doc parents %d\n", STDOUT_FILENO);
        // printf("should be printed\n");
        waitpid(heredoc_pid, &wstatus, 0);
    }
    // printf("goes\n");
    waitpid_status(wstatus); //, pid);
}

char *find_path(char **env)
{
    char *path;
    int i;
    int j;

    i = 0;
    path = NULL;
    while (env[i])
    {
        j = 0;
        while (env[i][j])
        {
            if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
            {
                path = env[i];

                return (ft_strdup(path + 5));
            }
            j++;
        }
        i++;
    }
    return (path);
}

char *find_right_path(char *argv, char **path, char ***split_cmd)
{
    t_path s_p;

    // ft_putstr_fd(path, 2);
    s_p.split_path = ft_split_add_slush(*path, ':');
    s_p.i = 0;
    if (access(*split_cmd[0], X_OK) == 0)
        return (ft_strdup(*split_cmd[0])); // because it might cause double free later when freeing split_cmd[0]
    else if (argv[0] != '/' && access(*split_cmd[0], X_OK) == -1)
    {
        // printf("findpath argv : %s\n", argv);
        while (s_p.split_path[s_p.i])
        {
            s_p.tmp = ft_strjoin(s_p.split_path[s_p.i], *split_cmd[0]);
            if (access(s_p.tmp, X_OK) == 0)
            {
                // printf("s_p.tmp : %s\n", s_p.tmp);
                all_free(&s_p.split_path);
                return (s_p.tmp);
            }
            s_p.i++;
            if (s_p.tmp)
            {
                free(s_p.tmp);
                s_p.tmp = NULL;
            }
        }
    }
    if (s_p.split_path)
        all_free(&s_p.split_path);

    // ft_putstr_fd("jj\n", 2);
    return (NULL);
}
// #include <fcntl.h>

// int isValidFD(int fd)
// {
//     int i = fcntl(fd, F_GETFD);
//     return (i);
// }

void execution(char *argv, char **env)
{
    char *path;
    char *cmd_path;
    char **split_cmd;

    split_cmd = NULL;
    cmd_path = NULL;
    if (argv[0] == '\0')
    {
        errors("zsh", 2, argv, NULL);
        exit(FAILED);
    }
    split_cmd = ft_split(argv, ' ');
    if (!split_cmd || !split_cmd[0])//안에 \0남아있는거랑 아에 NULL이랑은 달라.
    {
        errors("zsh", 0, "", NULL);
        if (split_cmd)
            all_free(&split_cmd);
        exit(FAILED);
    }
    if (split_cmd[0][0] == '.')// need to check in the school computer how it work
    {
        if (access(split_cmd[0], X_OK) == -1)
            errors("zsh", 2, split_cmd[0], NULL);
        else
            errors("zsh", 3, split_cmd[0], "is a directory: ");
        all_free(&split_cmd);
        exit(FAILED);
    }

    if (split_cmd[0][0] == '/' && access(split_cmd[0], X_OK) == -1)
    {
        errors("zsh", 3, split_cmd[0], "No such file or directory: ");
        all_free(&split_cmd);
        exit(FAILED);
    }
        // ft_putstr_fd(split_cmd[0], 2);
        // ft_putstr_fd("\n\n", 2);
        path = find_path(env);
    // ft_putstr_fd(path, 2);
    if (!path && access(split_cmd[0], X_OK) == -1)
    {
        errors("zsh", 0, (split_cmd)[0], NULL);
        // errors("zsh", 3, split_cmd[0], "No such file or directory:"); //in bash it will printed out like this
        all_free(&split_cmd);
        exit(FAILED);
    }
    cmd_path = find_right_path(argv, &path, &split_cmd);
    // ft_putstr_fd(argv, 2);
    // ft_putstr_fd(cmd_path,2);
    // ft_putstr_fd("\n\n",2);

    // if (!cmd_path)
    // {
    //     errors("zsh", 0, (split_cmd)[0]);
    //     split_cmd = all_free(split_cmd);
    //     exit(FAILED);
    // }
    // if (cmd_path && cmd_path[0] == '.') // cmd_path 안하면 seg나
    // {
    //     errors("zsh", 2, cmd_path);
    //     all_free(&split_cmd);
    //     free(cmd_path);
    //     cmd_path = NULL; // NULL 값을 할당하여 다시 해제할 수 없도록 만듦
    //     exit(FAILED);
    // }
    // 이부분도 필요없는게 다른 error메세지를 넣어주려고 한것인데,
    // 이미 execve는 자동으로 알아서 맞는 실행커멘트 파일의 위치를 찾는데 실패할 경우에는 -1으로 취급되어 그 밑으로 실행가능하고 free()같은 뒷처리를 해야한다.
    // 그 위의 부분을 제외한 execve()실패일 경우에는 옵션 에러, syntax에러와 같은 부분은 알아서 터미널에 에러메세지를 전달해주고, 직후의 코드들은 실행불가능하여, 알아서 free()되어진다.

    // 따라서 execve() 함수가 실패한 경우에는 현재 프로세스가 종료되고 새로운 프로세스로 대체되므로,
    // 해당 프로세스가 사용한 모든 메모리와 자원은 운영체제에 의해 자동으로 해제됩니다.
    // 이러한 이유로 실패한 경우에는 이미 메모리와 자원이 해제된 상태이므로, 해당 변수를 다시 해제할 필요가 없습니다.

    if (execve(cmd_path, split_cmd, (char *const *)env) == -1)
    {
        // execve는 자동으로 알아서.. 맞는 실행커멘트 파일의 위치를 실패할 경우에는 밑에  알아서 execve() 함수 호출 직후에 출력하고
        errors("zsh", 0, (split_cmd)[0], NULL);
        if (split_cmd)
            all_free(&split_cmd);
        if (cmd_path) // keep showing me that i have double freed it. why?
        {
            // ft_putstr_fd("\ncmd_path\n",2);
            free(cmd_path);
            cmd_path = NULL;
        }
        exit(FAILED);
    }
    // 네, 맞습니다.execve() 함수를 호출하면 이전 프로그램의 메모리 및 자원은 자동으로 해제되므로 별도로 free() 함수를 호출할 필요가 없습니다.
    // if (execve(*cmd_path, (char *const[]){"grep", ".c", NULL}, (char *const *)env) == -1)
    //     return (errors(first_cmd));
    // printf("should not print out\n");
    /*
    네, execve() 함수 호출 이후에는 이전의 프로그램에 존재하는 메모리를 해제할 필요가 없습니다.
    execve() 함수는 현재의 프로세스를 새로운 프로그램으로 완전히 교체하기 때문에,
    이전 프로그램에서 사용되던 모든 메모리는 더 이상 현재 프로세스에 의해 참조되지 않습니다.
    이에 따라 운영 체제는 이전 프로그램에 할당되었던 메모리를 자동으로 해제합니다.
    따라서 execve() 함수 호출 이후에는 이전 프로그램에 사용된 메모리를 해제할 필요가 없습니다.
    메모리 누수가 발생하지 않습니다.
    */
}

// void childprocess(char *argv, char **env, char **cmd_path)
// {
//     t_main child;

//     printf("Step 1\n");
//     if (pipe(child.fd) == -1)
//         errors("zsh");
//     printf("Step 2\n");
//     child.pid = fork();
//     if (child.pid == -1)
//         errors("zsh");
//     printf("Step 3\n");
//     int valid;
//     if ((valid = isValidFD(child.fd[1])) == -1)
//         printf("fd is not valid\n");
//     else
//         printf("fd is valid : %d\n", valid);
//     if (child.pid == 0)
//     {
//         close(child.fd[0]);
//         printf("fd[1] : %d\n", child.fd[1]);
//         printf("STDOUT_FILENO : %d\n", STDOUT_FILENO);
//         if (dup2(child.fd[1], STDOUT_FILENO) == -1)//그 다음행보인 execve()이상이 생긴건데 여기에도 문제가 생긴다. bad address라고. execve()는 스스로 이전의fd를 복사해와 새로은 프로세스를 만들어 실행하게되서 fd에 문제가 생길경우 문제가 생길 수 있다.
//         {
//             printf("entered -1");
//             errors("zsh");
//         }
//         // close(child.fd[1]); //이때는 하면안돼 열려있어야 execve할때 쓰지
//         printf("after dup2\n");
//         execution(argv, env, cmd_path);
//     }

//     printf("Step 4\n");
//     if (child.pid != 0)
//     {
//         close(child.fd[1]); // 독립적이라 괜찮은데...
//         printf("problem2?\n");
//         if (dup2(child.fd[0], STDIN_FILENO) == -1)
//             errors("zsh ");
//         printf("problem2?\n");
//         wait(&child.wstatus);
//         free_one(cmd_path);
//         close(child.fd[0]);
//     }
//     printf("Step 5\n");
//     waitpid_status(child.wstatus);
//     printf("Step 6\n");
// }
void childprocess(char *argv, char **env, t_data *data)
{
    int fd[2];
    int pid;
    int wstatus;

    wstatus = -1;
    // printf("wstatus : %d\n", wstatus);
    if (pipe(fd) == -1)
        errors("childprocess_pipe", 1, NULL, NULL);
    pid = fork();
    if (pid == -1)
        errors("childprocess_pid", 1, NULL, NULL);
    // ft_putnbr_fd(pid,2);
    // ft_putstr_fd("\n", 2);
    if (pid == 0)
    {
        if (data->i == (data->argc - 2))
        {
            // printf("before dup2 outfile : main :%d\n", outfile);
            if (dup2(data->outfile, STDOUT_FILENO) == -1)
                errors("oufile->dup2", 1, NULL, NULL);
            // printf("outfile : main :%d\n", outfile);
            close(data->outfile);
            // printf("STDOUT_FILENO : child process child %d\n", STDOUT_FILENO);
        }
        else
        {
            close(fd[0]);
            // int valid;
            // if ((valid = isValidFD(fd[1])) == -1)
            //     printf("fd is not valid\n");
            // else
            //     printf("fd is valid : %d\n", valid);
            // printf("fd[1] : %d\n", fd[1]);
            // printf("STDOUT_FILENO : %d\n", STDOUT_FILENO);
            if (dup2(fd[1], STDOUT_FILENO) == -1) // 그 다음행보인 execve()이상이 생긴건데 여기에도 문제가 생긴다. bad address라고. execve()는 스스로 이전의fd를 복사해와 새로은 프로세스를 만들어 실행하게되서 fd에 문제가 생길경우 문제가 생길 수 있다.
                errors("childprocess_dup2", 1, NULL, NULL);
            close(fd[1]);
            // perror("dup2");//뭔지 모르겠지만 이걸하면 invalid argument라고 계속 뜨긴뜸 .... 실행은 잘됌...
            // ft_putstr_fd("child_process after dup2", 2);
            // bottom ones will not able to printed out as the fd[1] changed to stdout and it will directly pass to the next cmd of stdin
            // that is why to use ft_putstr_fd() in order to print with fd strerr 2
            // printf("fd[1] : child process child %d\n", fd[1]);
            // printf("STDOUT_FILENO : child process child %d\n", STDOUT_FILENO);
        }
        execution(argv, env);
    }
    else
    {
        close(fd[1]);
        // printf("fd[0] : %d\n", fd[0]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
            errors("parentsprocess_dup2", 1, NULL, NULL);
        // printf("fd[0] : child process parents : %d\n", fd[0]);
        close(fd[0]);
        // printf("STDIN_FILENO :child process parents: %d\n", STDIN_FILENO);
        wait(&wstatus);
        // if (cmd_path) 독립적인 개체라 자식프로세스에서 받아온다한들 값이 바뀌지는 않아. 해줄필요가 없는거지
        //     free_one(cmd_path);
    }
    // printf("Step 5\n");
    waitpid_status(wstatus); //, pid);
    // printf("Step 6\n");
}

// void childprocess(char *argv, char **env, char **cmd_path, char ***split_cmd)
// {
//     int fd[2];
//     int pid;
//     int wstatus;

//     wstatus = -1;
//     // printf("wstatus : %d\n", wstatus);
//     if (pipe(fd) == -1)
//         errors("childprocess_pipe", 1, NULL);
//     // printf("Step 2\n");
//     pid = fork();
//     if (pid == -1)
//         errors("childprocess_pid", 1, NULL);
//     // printf("Step 3\n");
//     if (pid == 0)
//     {
//         close(fd[0]);
//         // int valid;
//         // if ((valid = isValidFD(fd[1])) == -1)
//         //     printf("fd is not valid\n");
//         // else
//         //     printf("fd is valid : %d\n", valid);
//         // printf("fd[1] : %d\n", fd[1]);
//         // printf("STDOUT_FILENO : %d\n", STDOUT_FILENO);
//          if (dup2(fd[1], STDOUT_FILENO) == -1) // 그 다음행보인 execve()이상이 생긴건데 여기에도 문제가 생긴다. bad address라고. execve()는 스스로 이전의fd를 복사해와 새로은 프로세스를 만들어 실행하게되서 fd에 문제가 생길경우 문제가 생길 수 있다.
//             errors("childprocess_dup2", 1, NULL);
//         close(fd[1]);
//         // perror("dup2");//뭔지 모르겠지만 이걸하면 invalid argument라고 계속 뜨긴뜸 .... 실행은 잘됌...
//         // ft_putstr_fd("child_process after dup2", 2);
//         // bottom ones will not able to printed out as the fd[1] changed to stdout and it will directly pass to the next cmd of stdin
//         //that is why to use ft_putstr_fd() in order to print with fd strerr 2
//         // printf("fd[1] : child process child %d\n", fd[1]);
//         // printf("STDOUT_FILENO : child process child %d\n", STDOUT_FILENO);
//         execution(argv, env, cmd_path, split_cmd);
//     }
//     else
//     {
//         close(fd[1]);
//         // printf("fd[0] : %d\n", fd[0]);
//         if (dup2(fd[0], STDIN_FILENO) == -1)
//             errors("parentsprocess_dup2", 1, NULL);
//         // printf("fd[0] : child process parents : %d\n", fd[0]);
//         close(fd[0]);
//         // printf("STDIN_FILENO :child process parents: %d\n", STDIN_FILENO);
//         wait(&wstatus);
//         // if (cmd_path) 독립적인 개체라 자식프로세스에서 받아온다한들 값이 바뀌지는 않아. 해줄필요가 없는거지
//         //     free_one(cmd_path);
//     }
//     // printf("Step 5\n");
//     waitpid_status(wstatus);//, pid);
//     // printf("Step 6\n");
// }

int check_heredoc(int *outfile, int *i, char **argv, int argc)
{
    int infile;

    if (ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        // printf("b_outfile : %d\n", *outfile);
        *outfile = open_file(argv[argc - 1], 1, 1);
        // printf("outfile : %d\n", *outfile);
        here_doc(argc, argv[2]); // 얘가 오류가 났다고 해도 계속 진행되어야해. -> input을 받아오는거라 에러가 나서는 안됌.
        // printf("repeat\n");
        *i = 3;
    }
    else
    {
        infile = open_file(argv[1], 0, 0); // 앤 중단해야되 infile 없으면? 맞나?
        // printf("infile : %d\n", infile);
        *outfile = open_file(argv[argc - 1], 1, 0);
        // printf("outfile : %d\n", *outfile);
        if (infile == -1 || *outfile == -1)
            return (FAILED);
        // printf("before dup2 infile: %d\n", infile);
        if (dup2(infile, STDIN_FILENO) == -1)
            errors("infile->dup2", 1, NULL, NULL);
        close(infile);
        // perror("dup2");
        *i = 2;
    }
    return (SUCCESS);
}
int main(int argc, char **argv, char **env)
{
    t_data data;

    data.i = 0;
    data.argc = argc;
    // uid_t uid = getuid(); // 현재 사용자의 UID(사용자 식별자)를 얻어옵니다.
    // gid_t gid = getgid(); // 현재 사용자의 기본 그룹의 GID(그룹 식별자)를 얻어옵니다.

    // ft_putstr_fd("\n", 2);
    // ft_putnbr_fd(gid,2);
    // ft_putstr_fd("\n", 2);
    if (argc >= 5)
    {
        if (check_heredoc(&data.outfile, &data.i, argv, argc) == -1)
            return (FAILED);
        while (data.i <= (argc - 2))
        {
            childprocess(argv[data.i], env, &data); // 동시에 시작되면서 &file의 값이 바뀌어버림.
            data.i++;
        }
    }
    else
    {
        // while (1)
        // {
        // }
        return (error_syntax(0));
    }
    // while (1)
    // {
    // }
    return (0);
}
// int main(int argc, char **argv, char **env)
// {
//     int outfile;
//     int i;
//     char *cmd_path;
//     char **split_cmd;

//     split_cmd = NULL;
//     cmd_path = NULL;
//     i = 0;

//     if (argc >= 5)
//     {
//         if (check_heredoc(&outfile, &i, argv, argc) == -1)
//             return (FAILED);
//         while (i < (argc - 2))
//         {
//             // printf("\n\nchildprocess %d \n\n", i);
//             childprocess(argv[i], env, &cmd_path, &split_cmd); // 동시에 시작되면서 &file의 값이 바뀌어버림.
//             i++;
//         }
//         // printf("before dup2 outfile : main :%d\n", outfile);
//         if (dup2(outfile, STDOUT_FILENO) == -1)
//             errors("oufile->dup2", 1, NULL);
//         // printf("outfile : main :%d\n", outfile);
//         close(outfile);
//         // printf("STDOUT_FILENO : child process child %d\n", STDOUT_FILENO);
//         execution(argv[argc - 2], env, &cmd_path, &split_cmd); // 마지막 cmd하나는 실행시키기로하다가 waitpid_stauts()때매 하지않으려했는데 생각해보니 child는 다끊나고없어 필요가없엄
//     }
//     else
//     {
//         while (1)
//         {
//             ft_putstr_fd("dd",2);
//         }
//         return (error_syntax(0));
//     }
//     while (1)
//     {
//         ft_putstr_fd("dd", 2);
//     }
//     return (0);

// }
