/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/12 23:09:41 by suminkwon        ###   ########.fr       */
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

# define BUFFER_S 4096

typedef struct s_path
{
    // int fd[2]; // do you need?
    // int pid; // also this will directly copied while fork()
    char **env;
    char **path;
    // char **each_arg_cmd;
    char ***argvs_cmd;
    // char **final_cmd_path;
    

}              t_path;

// typedef struct s_read
// {
//     char *buffer;
//     // char *passage_read;
//     int bytes_read;

// }               t_read;

typedef struct s_main
{
    int fd[2];
    int pid;
    int infile;
    int oufile;
}               t_main;
t_path *new_struct(char **env);
char **ft_split_add_slush(char const *s, char c);
char **all_free(char **res);

char *find_path(char **env);
int split_path(t_path **path_data);
int find_right_cmd_path(t_path **path_data, int i);
int split_argv(char **argv, t_path **path_data, int argc);
int check_wholepath_argv(t_path **path_data);
#endif

