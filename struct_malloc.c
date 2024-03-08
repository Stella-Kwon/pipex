/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:43:42 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/08 17:44:18 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_path *new_struct(char **env)
{
    t_path *res;
    
    res = (t_path *)malloc(sizeof(t_path));
    if (!res)
    {
        printf("there is null in res in new_struct()\n");
        return (NULL);
    }
    res->env = env;
    res->path = NULL;
    // res->exec_cmd = NULL;
    res->argvs_cmd = NULL;
    return(res);
}