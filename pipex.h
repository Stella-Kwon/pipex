/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/14 15:27:28 by skwon2           ###   ########.fr       */
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
# define SUCCESS 0
# define FAILED -1

// typedef struct s_path
// {
    // char **env;
    // char **path;
    // char ***argvs_cmd;
// }              t_path;

// typedef struct s_read
// {
//     char *buffer;
//     // char *passage_read;
//     int bytes_read;

// }               t_read;

typedef struct s_main
{
    int fd[2];
    pid_t pid;
    int infile;
    int oufile;
}               t_main;

// t_path *new_struct(char **env);
char **ft_split_add_slush(char const *s, char c);
char **all_free(char **res);
// void	error(void);
char *find_path(char **env);
char **split_path(char **env);
char **find_right_path(char **env, int i, char **argv, int argc)
#endif

