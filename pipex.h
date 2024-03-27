/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/03/27 19:45:33 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"

# define FAILED -1
# define SUCCESS 1

typedef struct s_path
{
	char	**split_path;
	char	*tmp;
	int		i;
}				t_path;

typedef struct s_data
{
	int	i;
	int	argc;
	int	outfile;
}				t_data;

typedef struct s_line
{
	char	c;
	int		r_byte;
	int		i;
	int		buf_size;
}				t_line;

char	**ft_split_add_slush(char const *s, char c);
char	**all_free(char ***res);
int		errors(char *prefix, int n, char *file, char *extra);
int		error_syntax(int heredoc);
int		open_file(char *file, int fileno, int heredoc);
int		waitpid_status(int wstatus);
int		read_line(char **line);
int		ft_charjoin(char **line, t_line *readline);
void	heredoc_child(int (*heredoc_fd)[2], char *limiter);
void	here_doc(int argc, char *limiter);
int		not_heredoc(int *outfile, char **argv, int argc);
int		check_heredoc(int *outfile, int *i, char **argv, int argc);
char	*find_path(char **env);
char	*find_right_path(char *argv, char **path, char ***split_cmd);
void	free_one(char **str);
int		split_cmd_error(char	***split_cmd);
int		top_execution(char *argv, char **env, char **path, char	***split_cmd);
void	execution(char *argv, char **env);
void	child_childprocess(char *argv, char **env, int *fd, t_data *data);
void	childprocess(char *argv, char **env, t_data *data);
#endif
