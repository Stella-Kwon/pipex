/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:52 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/07 15:22:42 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
    int fd[2];
    int pid;
    t_pipe data;
    
    if (pipe(fd) == -1)
    {
        perror("Failed to generate pipe");
        return (0);
    }
    
    while (pid)
    {
        
        if (pid == 0)
        {
            child process // need to end.
            if ()
            {
                
            }
        }
        else
        {
            fork();
        }
    }
    return (0);
}
