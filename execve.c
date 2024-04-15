/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:06:18 by suminkwon         #+#    #+#             */
/*   Updated: 2024/04/14 21:24:28 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int split_cmd_error(char ***split_cmd)
{
    if (!(*split_cmd))
    {
        ft_putstr_fd("spli_cmd failed splitting with space", 2);
        return (FAILED);
    }
    if ((*split_cmd)[0][0] == '.')
    {
        if (access((*split_cmd)[0], X_OK) == -1)
        {
            errors("bash: ", 0, NULL, (*split_cmd)[0]);
            all_free(split_cmd);
            if (access("filename", F_OK) == -1)
            {
                // 파일이 존재하지 않음
                return (126);
            }
            return (127);
        }
        else
            errors("bash", 1, (*split_cmd)[0], "is a directory");
        all_free(split_cmd);
        return (126);
    }
    if ((*split_cmd)[0][0] == '/' && access((*split_cmd)[0], X_OK) == -1)
    {
        errors("bash", 1, (*split_cmd)[0], "No such file or directory");
        all_free(split_cmd);
        return (127);
    }
    return (SUCCESS);
}

int top_execution(char *argv, char **env, char **path, char ***split_cmd)
{
    int exitcode;

    
    if (argv[0] == '\0')
    {
        errors("bash", 1, argv, "command not found");
        return (127);
    }
    *path = find_path(env);
    // ft_putstr_fd("path : ", 2);
    // ft_putstr_fd(*path, 2);
    // ft_putchar_fd('\n', 2);
    if (count_words(argv, ' ') == 0)
    {
        if (!(*path))
            errors("bash", 1, argv, "No such file or directory");
        else
            errors("bash", 1, argv, "command not found");
        return (127);
    }
    // *split_cmd = ft_split(argv, ' ');
    *split_cmd = ft_split_several(argv, ' ', '"','\'');
    exitcode = split_cmd_error(split_cmd);
    if (exitcode != SUCCESS)
        return (exitcode);
    // ft_putstr_fd("split_cmd: ", 2);
    // ft_putstr_fd((*split_cmd)[0], 2);
    // ft_putchar_fd('\n', 2);
    if (!(*path) && access((*split_cmd)[0], X_OK) == -1)
    {
        errors("bash", 1, (*split_cmd)[0], "No such file or directory");
        all_free(split_cmd);
        return (127);
    }
    // ft_putendl_fd("end of split_cmd_error()",2);
    return (SUCCESS);
}

int execution(char *argv, char **env)
{
    char *path;
    char *cmd_path;
    char **split_cmd;
    int exitcode;

    split_cmd = NULL;
    cmd_path = NULL;
    path = NULL;
    exitcode = top_execution(argv, env, &path, &split_cmd);
    if (exitcode != SUCCESS)
    {
        // ft_putstr_fd("top_exection:", 2);
        // ft_putnbr_fd(exitcode, 2);
        // ft_putstr_fd("\n", 2);
        return (exitcode);
    }
    // ft_putendl_fd("after top execution",2);
    cmd_path = find_right_path(argv, &path, &split_cmd);
    // if (!cmd_path)
    // {
    // 	ft_putstr_fd("cmppath : 127\n", 2);
    // 	return (127);
    // }
    // ft_putendl_fd("after comd_path",2);
    if (execve(cmd_path, split_cmd, (char *const *)env) == -1)
    {
        // ft_putstr_fd("Errno : ", 2);
        // ft_putnbr_fd(errno, 2);
        errors("bash", 1, (split_cmd)[0], "command not found");
        if (split_cmd)
            all_free(&split_cmd);
        free_one(&cmd_path);
    }
    return (127);
}

// int	close_all(t_fork **p)
// {
// 	int	i;

// 	i = 0;
//     // ft_putstr_fd(" cmdscount : ", 2);
//     // ft_putnbr_fd((*p)->cmdscount, 2);
//     // ft_putstr_fd("\n", 2);
// 	while (i < (*p)->cmdscount - 1)
// 	{
//         // ft_putstr_fd("i : ", 2);
//         // ft_putnbr_fd(i, 2);
//         // ft_putstr_fd("\n", 2);
// 		if (close((*p)->fd[i][WRITE]) == -1)
// 			return (FAILED);
// 		if (close((*p)->fd[i][READ]) == -1)
// 			return (FAILED);
// 		i++;
// 	}
// 	return (SUCCESS);
// }