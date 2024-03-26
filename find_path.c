/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:25:23 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/17 13:46:41 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// malloc최대한없애기로 한다 비효율적 => struct없이 해줘도 될거같애.왜냐 사용하는곳이 한정적. exeve쓸때만.
// 그리고 argv[1]open하면서 이미 파일형태가 아니면 에러나오게 핸들링.
//  그냥 access에서 이미다 체크하니까 cmd그냥 다 argvs넣어줘도 상관없을거같다.
// char *find_path(char **env)
// {
//     char *path;
//     int i;
//     int j;

//     i = 0;
//     path = NULL;
//     while (env[i])
//     {
//         j = 0;
//         while (env[i][j])
//         {
//             if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
//             {
//                 path = env[i];

//                 return (ft_strdup(path + 5));
//             }
//             j++;
//         }
//         i++;
//     }
//     return (path);
// }

// int split_path(t_path **path_data)
// {
    // char *path;
    // path = find_path(env);
    // if (!path)
    // {
    //     printf("path is NULL which means env is null : check env and find_path()\n");
    //     return (-1);
    // }
    // (*path_data)->path = (char **)malloc(sizeof(path));
    // if (!(*path_data)->path)
    // {
    //     printf("(*path_data)->path is NULL : check split_path()\n");
    //     return (-1);
    // }
    // (*path_data)->path= ft_split_add_slush(path, ':');
    // if (!(*path_data)->path)
    // {
    //     printf(" (*path_data)->path is NULL : check split_path() -> ft_split(), it has problem \n");
    //     return (-1);
    // }
    // int i;
    // int j = 0;
    // i = 0;
    // printf("\n\n\npath:\n");
    // while((*path_data)->path[i])
    // {
    //     j = 0;
    //     while((*path_data)->path[i][j])
    //     {
    //         printf("%c", (*path_data)->path[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }
    // printf("\n");
    // return (1);
// }

char ***split_argv(char **argv, int argc)
{
    char **each_arg_cmd;
    int arg_cmd_len;
    int i;
    int j;

    argvs_cmd = (char ***)malloc(sizeof(char **) * ((argc - 3) + 1));
    if (!argvs_cmd)
    {
        printf("argvs_cmd is NULL : check split_argv\n");
        return (-1);
    }
    i = 0;
    while (argv[i] && i < (argc - 3))
    {
        each_arg_cmd = ft_split(argv[i], ' ');
        if (!each_arg_cmd)
        {
            printf("each_arg_cmd is null : check check_argv() after split \n");
            // i 이전의 argvs에 대한  each_arg_cmd 값을 해제해준다.
            if (argvs_cmd[i])
                all_free(argvs_cmd[i]);
            free(argvs_cmd);
            return (-1);
        }
        // printf("\n\n\neach_arg_cmd : \n");
        // j = 0;
        // while (each_arg_cmd[j])
        // {
        //     printf("each_arg_cmd[%d] %s\n", j, each_arg_cmd[j]);
        //     j++;
        // }
        // printf("\n");

        arg_cmd_len = 0;
        while (each_arg_cmd[arg_cmd_len])
            arg_cmd_len++;
        // 이렇게 malloc또 안해주면 제대로된값을 받아오지 못함.
        //  printf("arg_cmd_len :  %d\n", arg_cmd_len);
        argvs_cmd[i] = (char **)malloc((arg_cmd_len + 1) * sizeof(char *));
        if (!argvs_cmd[i])
        {
            printf("Memory allocation failed\n");
            return (-1);
        }
        // each_arg_cmd가 계속 바뀌기 떄문에.... 복사해서 넣어줘야한다.
        j = 0;
        while (each_arg_cmd[j])
        {
            argvs_cmd[i][j] = ft_strdup(each_arg_cmd[j]);
            if (!argvs_cmd[i][j])
            {
                printf("argvs_cmd[i][j] ft_strdup failed : int split_argv()\n");
                return (-1);
            }
            j++;
        }
        argvs_cmd[i][j] = NULL;
        all_free(each_arg_cmd);
        i++;
        printf("i : %d\n", i);
    }
    argvs_cmd[i] = NULL;

    // printf("\n\n\nargvs_cmd : \n");
    // i = 0;

    // while(argvs_cmd[i])
    // {
    //     j = 0;
    //     while(argvs_cmd[i][j])
    //     {
    //         printf("argvs_cmd[%d][%d] : %s\n", i, j, argvs_cmd[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }
    // printf("\n\n\n");
    return (1);
}

int find_right_cmd_path(char **path, char ***argvs_cmd, int i, char **env)
{
    int j;
    char *tmp;

    j = 0;
    while ((path[j]))
    {
        tmp = ft_strjoin(path[j], argvs_cmd[i][0]);
        if (!tmp)
        {
            printf("tmp is null in check_wholepath_argv() : check after ft_strjoin()\n");
            return (-1);
        }
        if (access(tmp, X_OK) == 0)
        {
            argvs_cmd[i][0] = tmp;
            printf("argv[%d][0] %s\n", i, argvs_cmd[i][0]);
            return (1);
        }
        else // if (access(tmp, X_OK) == -1)
        {
            // printf("tmp :  %s\n", tmp);
            free(tmp);
            // perror("find_right_cmd_path");
        }
        j++;
    }
    all_free(path);
        i = 0;
        printf("\n\n\nargvs_cmd : \n");
        while(argvs_cmd[i])
        {
        int j = 0;
        while (argvs_cmd[i][j])
        {
            printf("argv[%d][%d] %s\n", i, j, argvs_cmd[i][j]);
            j++;
        }
        printf("\n");
        i++;
        }
        printf("\n");
        return (-1);
}

int check_wholepath_argv(char **env, char **argv,int argc)
{
    int i;
    int j;
    char *pre_path;
    char **path;
    char ***argvs_cmd;

    i = 0;
    j = 0;
    while (!(pre_path = ft_strnstr(env[j], "PATH =", ft_strlen(env[j]))) && env[j])
        j++;
    path = ft_split_add_slush(pre_path + 5, ':');
    argvs_cmd = split_argv(argv + 2, argc);
    while (argvs_cmd[i])
    {
        // int z = 0;
        // printf("\n\n\nargvs_cmd : \n");
        // while(argvs_cmd[z])
        // {
        //     int j = 0;
        //     while(argvs_cmd[z][j])
        //     {
        //         printf("argv[%d][%d] %s\n", z, j, argvs_cmd[z][j]);
        //         j++;
        //     }
        //     printf("\n");
        //     z++;
        // }
        // printf("\n");
        // if (access(argvs_cmd[i][0], X_OK) == 0)
        // {
        //     printf("with the right path already");
        //

        // }
        if (access(argvs_cmd[i][0], X_OK) == -1)
        {
            if (find_right_cmd_path(path, i, env) == -1)
            {
                perror("access error, gonna do find_right_cmd_path()");
                printf("find_right_cmd_path() error : check_wholepath_argv\n");
                return (-1);
            }
        }
        i++;
    }
    return (1);
}

int main(int argc, char **argv, char **env)
{
    t_path *path_data;
    int i;
    int j;
    // int pid;

    // -----------------env---------------
    // i = 0;
    // printf("\n\n\nenv: ");
    // while(env[i])
    // {
    //     j = 0;
    //     while(env[i][j])
    //     {
    //         printf("%c", env[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }
    // printf("\n");
    //// -----------------argv---------------
    i = 0;
    printf("\n\n\nargv:");
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            printf("%c", argv[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
    path_data = new_struct(env);
    printf("argc : %d \n", argc);
    // if (split_path(&path_data) == -1)
    //     return (-1);
    // if (split_argv(argv + 2, &path_data, argc) == -1)
    //     return (-1);
    if (check_wholepath_argv(env, argv, env) == -1)
        perror("main");
        return (-1);

    // -----------------final path ---------------
    // printf("\n\nfinal path\n\n");
    // i = 0;
    // while(path_data->argvs_cmd[i])
    // {
    //     j = 0;
    //     // while (path_data->argvs_cmd[i][0]) => 0 때문에 segmentation fault에러가 난다.
    //     /*
    //     path_data->argvs_cmd[i]는 i번째 명령어에 대한 인수들을 저장하는 포인터 배열입니다.
    //     이 배열의 마지막 요소는 NULL 포인터로 종료됩니다. 그러나 코드에서는 path_data->argvs_cmd[i][0]만을 검사하고 있으므로,
    //     먼저 i가 NULL에 다다르고 [0]관련 access가 불가능해서 저렇게 나오는것 같다.
    //     이로 인해 유효하지 않은 메모리에 접근하려고 하게 되어 segmentation fault가 발생합니다.
    //     */
    //     while (path_data->argvs_cmd[i][0][j])
    //         {
    //             printf("%c", (path_data)->argvs_cmd[i][0][j]);
    //             j++;
    //         }
    //     printf("\n");
    //     i++;
    // }
    return 0;
}
