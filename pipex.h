/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/08 17:47:53 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./Libft/libft.h"

typedef struct s_path
{
    // int fd[2]; // do you need?
    //int pid; // also this will directly copied while fork()
    char **env;
    char **path;
    // char **each_arg_cmd;
    char ***argvs_cmd;
    // char **final_cmd_path;

}              t_path;

t_path *new_struct(char **env);

#endif

