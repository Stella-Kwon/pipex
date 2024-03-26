/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/26 22:04:11 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "./Libft/libft.h"

// # define BUFFER_S 4096


# define FAILED -1
# define SUCCESS 1
    typedef struct s_path
{
    char **split_path;
    char *tmp;
    int i;
}              t_path;
typedef struct s_data
{
    int i;
    int argc;
    int outfile;
}               t_data;

typedef struct s_line
{
    char c;
    int r_byte;
    int i;
    int buf_size;
}               t_line;

// typedef struct s_main
// {
//     int fd[2];
//     pid_t pid;
//     int wstatus;
// }               t_main;
t_path *new_struct(char **env);
char **ft_split_add_slush(char const *s, char c);
char **all_free(char ***res);

char *find_path(char **env);
int split_path(t_path **path_data);
// int find_right_cmd_path(t_path **path_data, int i);
int find_right_cmd_path(char **path, char ***argvs_cmd, int i, char **env);
char ***split_argv(char **argv, int argc);
// int split_argv(char **argv, t_path **path_data, int argc);
// int check_wholepath_argv(t_path **path_data);
int check_wholepath_argv(char **env, char **argv, int argc);
#endif

