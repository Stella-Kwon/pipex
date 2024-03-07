/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/07 15:08:34 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_pipe
{
    // int fd[2]; // do you need?
    //int pid; // also this will directly copied while fork()
}              t_pipe;
#endif

