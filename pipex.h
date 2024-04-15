/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:25:22 by skwon2            #+#    #+#             */
/*   Updated: 2024/04/14 20:05:16 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"

# define FAILED 1
# define SUCCESS 0
# define WRITE 1
# define READ 0

typedef struct s_path
{
	char	**split_path;
	char	*tmp;
	int		i;
}				t_path;

typedef struct s_data
{
	int		i;
	int		n;
	int		pipes;
	int		argc;
	int		infile;
	int		outfile;
	int		childstatus;
	char	**argv;
	int		checkheredoc;
	int		start;
}				t_data;

typedef struct s_line
{
	char	c;
	int		r_byte;
	int		i;
	int		buf_size;
}				t_line;

typedef struct s_fork
{
	int		**fd;
	pid_t	*pid;
	int		cmdscount;
	int		wstatus;
	int		exitcode;
}				t_fork;
typedef struct s_doc
{
	pid_t	pid;
	int		wstatus;
	int		exitcode;
}				t_doc;
typedef struct s_exec
{
	char	*path;
	char	*cmd_path;
	char	**split_cmd;
	int		exitcode;
}				t_exec;

char	**ft_split_add_slush(char const *s, char c);
char	**all_free(char ***res);
int		errors(char *prefix, int n, char *file, char *extra);
int		error_syntax(int heredoc);
int		open_file(char *file, int fileno, int heredoc);
int		waitpid_status(int wstatus);
int		read_line(char **line);
int		ft_charjoin(char **line, t_line *readline);
int		heredoc_child(int fd, char *limiter);
int		here_doc(char *limiter, t_data *data);
void	initialize_data(t_data	*data, int argc, char **argv);
void	initialize_pipe(t_fork **pipe, t_data data);
int		check_heredoc(t_data *data);
char	*find_path(char **env);
char	*find_right_path(char *argv, char **path, char ***split_cmd);
void	free_one(char **str);
int		split_cmd_error(char ***split_cmd);
int		top_execution(char *argv, char **env, char **path, char ***split_cmd);
int		execution(char *argv, char **env);
int		child_childprocess(char *argv, t_fork **p, t_data *data, char **env);
int		childprocess(char *argv, char **env, t_data *data, t_fork **p);
int		cmds_action(t_fork **p, t_data *data);
int		first_cmd_action(t_fork **p, t_data *data);
int		last_cmd_action(t_fork **p, t_data *data);
void	free_pipe(t_fork **pipe);
int		parentsprocess(t_data *data, t_fork **p);
size_t	count_words(char *str, char c);
char	**split_path(char **path);
char	*strjoin_path(t_path *s_p, char ***split_cmd);
int		precheck(char ***split_cmd, char **tmp);
void	initialize_data(t_data	*data, int argc, char **argv);
char	**all_free_int(int ***res, int n);
int		ft_strcmp(const char *line, const char *limiter);
char	**all_free_int(int ***res, int n);
char	**ft_split_several(char const *s, char c, char s1, char s2);
#endif
