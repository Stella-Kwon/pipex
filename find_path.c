/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:25:23 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/08 18:40:47 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char **env)
{
    char    *path;
    int     i;
    int     j;
    
    i = 0;
    path = NULL;
    while (env[i])
    {
        j = 0;
        while(env[i][j])
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

int split_path(t_path **path_data)
{
    char *path;
    
    path = find_path((*path_data)->env);
    if (!path)
    {
        printf("path is NULL which means env is null : check env and find_path()\n");
        perror("env is empty :");
        return (-1);
    }
    (*path_data)->path = ft_split(path, ':');
    if (!(*path_data)->path)
    {
        printf(" (*path_data)->path is NULL : check ft_split(), it has problem \n");
        return (-1);
    }
    return (1);
}

int split_argv(char **argv, t_path **path_data)
{
    char **each_arg_cmd;
    int i;
    // int z;
    int j;

    i = 0;
    printf("argv[i]\n");
    printf("%s\n",argv[i + 1]);
    while (argv[i])
    {
        printf("hello\n");
        each_arg_cmd = ft_split(argv[i], ' ');
        printf("hello\n");
        if (!each_arg_cmd)
        {
            printf("each_arg_cmd is null : check check_argv() after split \n");
            return (-1);
        }
        // j = 0;
        // while (each_arg_cmd[j])
        // {
        //     printf("%s\n",each_arg_cmd[j]);
        // }
        (*path_data)->argvs_cmd[i] = each_arg_cmd;
        // j = 0;
        // while (each_arg_cmd[j])
        // {
        //     printf("%s\n",each_arg_cmd[j]);
        // }
        i++;
    }
    return (1);
}


int find_right_cmd_path(t_path **path_data, int i)
{
    int j;
    char *tmp;
    

    tmp = NULL;
    j = 0;
    while ((*path_data)->path[j])
    {
        tmp = ft_strjoin((*path_data)->path[j], (*path_data)->argvs_cmd[i][0]);
        if (!tmp)
        {
            printf("tmp is null in check_wholepath_argv() : check after ft_strjoin()\n");
            return (-1);
        }
        if (access(tmp, X_OK) == 0)
        {
            (*path_data)->argvs_cmd[i][0] = tmp;
        }
        else
        {
            perror("find_right_cmd_path");
            return (-1);
        }
        j++;
    }
    return (1);
}

int check_wholepath_argv(t_path **path_data)
{
    int i;
    
    i = 0;
    
    while ((*path_data)->argvs_cmd[i])
    {
        printf("dddd\n");  
        if (access((*path_data)->argvs_cmd[i][0], X_OK) == 0)
        {
            printf("with path already");
            break;
        }
        else
        {
            printf("dddddd\n");  
            if (find_right_cmd_path(path_data, i) == -1)
            {
                printf("find_right_cmd_path() error");
                return (-1);
            }
        }
        i++;
    }
    return (1);
}
// int valid_path(t_path *path_data) // it is already when argv is not null
// {
    
//     // if (!path_data->argvs_cmd)
//     // {
//     //     printf("path_data->path is null :  check split_path()\n");
//     //     return (-1);
//     // }

// }

int main(int argc, char **argv, char **env)
{
    t_path *path_data;
    int i;
    int j;

    //     i = 0;
    // printf("\n\n\nargv:");
    // while(argv[i])
    // {
    //     j = 0;
    //     while(argv[i][j])
    //     {
    //         printf("%c", argv[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }
    // printf("\n");
    path_data = new_struct(env);
    printf("d\n");
    if (split_path(&path_data) == -1)
        return (-1);
    printf("dd\n");
    if (split_argv(argv + 1, &path_data) == -1)
        return (-1);
    printf("ddd\n");
    // if (check_wholepath_argv(&path_data) == -1)
    //     return (-1);
    // printf("dddd\n");    
    // printf("\n\nfinal path\n\n");
    // i = 0;
    // while(path_data->argvs_cmd[i][0])
    // {
    //     j = 0;
    //     while(path_data->argvs_cmd[i][0][j])
    //     {
    //         printf("%c", (path_data)->argvs_cmd[i][0][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }
    return 0;
}

// int main (int argc, char **argv, char **env)
// {
//     char *path;
//     char **res;
//     int  i;
//     int  j;
    
//     res = NULL;
//     path = NULL;
//     i = 0;
//     printf("\n\n\nenv:");
//     while(env[i])
//     {
//         j = 0;
//         while(env[i][j])
//         {
//             printf("%c", env[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
//     printf("\n");
//     path = find_path(env);
//     if (!path)
//     {
//         printf("there is no path in env\n");
//         return 0;
//     }
//     printf("path\n\n");
//     i = 0;
//     while (path[i])
//     {
//         printf("%c", path[i]);
//         i++;
//     }
    
//     printf("\n");
//     res = split_path(path);
//     if (!res)
//         return 0;
//     printf("\n");
//     printf("\n");
//     printf("res\n\n");
//     i = 0;
//     while(res[i])
//     {
//         j = 0;
//         while(res[i][j])
//         {
//             printf("%c", res[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
//     printf("\n");
//     return (0);
// }