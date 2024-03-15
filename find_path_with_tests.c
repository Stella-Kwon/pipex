/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:25:23 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/15 14:18:38 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//malloc최대한없애기로 한다 비효율적 => struct없이 해줘도 될거같애.왜냐 사용하는곳이 한정적. exeve쓸때만.
//그리고 argv[1]open하면서 이미 파일형태가 아니면 에러나오게 핸들링.
// 그냥 access에서 이미다 체크하니까 cmd그냥 다 argvs넣어줘도 상관없을거같다.

// void	error(void)
// {
// 	perror("\033[31mError");
// 	exit(FAILED);
// }

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
            if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' \
            && env[i][3] == 'H')
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

char **split_path(char **env)
{
    char *path;
    char **split_path;
    
    path = find_path(env);
    if (!path)
    {
        printf("path is NULL which means env is null : check env and find_path()\n");
        return (NULL);
    }
    split_path= ft_split_add_slush(path, ':');
    if (!split_path)
    {
        printf(" path is NULL : check split_path() -> ft_split(), it has problem \n");
        return (NULL);
    }
    int i;
    int j = 0;
    i = 0;
    printf("\n\n\npath:\n");
    while(split_path[i])
    {
        j = 0;
        while(split_path[i][j])
        {
            printf("%c", split_path[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
    return (split_path);
}

char *find_right_path(char **env, char **argv)
{
    int     i;
    char *tmp;
    char **path;
    char **split_cmd;
    
    i = 0;
    path = split_path(env);
    if (!path)
        return (NULL);
    while (path[i])
    {
        split_cmd = ft_split(argv[i], ' ');
        printf("argv[i] :  %s\n", argv[i]);
        printf("cmd  : %s\n", split_cmd[0]);
        tmp = ft_strjoin(path[i], split_cmd[0]);
        if (!tmp)
        {
            printf("tmp is null in check_wholepath_argv() : check after ft_strjoin()\n");
            return (NULL);
        }
        if (access(tmp, X_OK) == 0)
        {
            all_free(path);
            all_free(split_cmd);
            return (tmp);
        }
        else
        {
            all_free(split_cmd);
            free(tmp);
        }
        i++;
    }
    printf("find right path : path %s\n ", tmp);
    all_free(path);
    perror("zsh ");
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    int i;
    int j;

    //// -----------------env---------------
    i = 0;
    printf("\n\n\nenv: ");
    while(env[i])
    {
        j = 0;
        while(env[i][j])
        {
            printf("%c", env[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
    //// -----------------argv---------------
    i = 0;
    printf("\n\n\nargv:");
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            printf("%c", argv[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
    printf("argc : %d\n",  argc);
    if (!find_right_path(env, argv))
    {
        return (-1);
    }
    return 0;
}
