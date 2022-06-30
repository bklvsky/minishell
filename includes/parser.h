/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:03:54 by dselmy            #+#    #+#             */
/*   Updated: 2022/06/30 13:24:32 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define SIMPLE_OUT 1
# define DOUBLE_OUT 2
# define SIMPLE_IN 3
# define DOUBLE_IN 4

int	g_exit_status;

typedef struct s_file
{
	char		*name;
	int			type_of_redirect;
	int			open_flags;
	int			is_heredoc;
	int			heredoc_pipe[2];
	int			ambiguous_redir;
}				t_file;

typedef struct s_token
{
	char		*token;
	size_t		size_of_token_line;
	char		**cmd;
	t_list		*files;
	int			pipefd[2];
	int			fd_in;
	int			fd_out;
	int			is_built_in;
}				t_token;

typedef struct s_data
{
	t_lst_d	*tokens;
	int		last_exit_status;
	char	*line;
	char	**env;
	char	*error_ident;
	char	*error_message;
	int		error_exit_code;
	int		interrupted;
}			t_data;

void	init_struct_first(t_data **all, char **env);
void	init_data(t_data *all, char *input);

t_lst_d	*new_token(void);
void	new_pipe_token(t_data *all);
int		parse_token(t_data *all);

int		parser(t_data *all);

int		write_in_cur_arg(int quoted_flag, char **arg, char *token, t_data *all);

void	make_new_cmd_arg(int *i, int *cmd_i, t_token *cur_token, t_data *all);
int		get_arg_len(int quoted_flag, char *token);
int		get_type_of_redirect(char *line, int *i);

int		manage_redirections(int *i, t_token *current_token, t_data *all);

int		expand_env_var(char **buf, char *source, t_data *all);
char	*get_var_name(char *line);

void	error_exit(t_data *all);
void	error_pipe_exit(t_lst_d *token, t_data *all);
void	error_launch_exit(t_lst_d *token, t_data *all);
int		error_launch_stop(t_lst_d *token, t_data *all);
int		error_syntax_exit(int err_index, t_lst_d *cur_token, t_data *all);
void	free_all(t_data *all);
void	free_cmd(t_data *all);
void	close_all(t_lst_d *token);
void	close_current(t_lst_d *token);
void	close_heredocs(t_lst_d *tokens);
void	put_error(t_data *all);
char	*get_unexpected_token(int err_index, t_lst_d *cur_token);

int		get_open_flags(int type_of_redirect);
int		open_all_files(t_token *token, t_data *all);

void	launch_minishell(t_data *all, int num_of_tokens);
int		redirect_fds(t_lst_d *token, t_data *all);
void	exec_cmd(char **cmd_args, t_data *all);
int		exec_builtin(t_token *token, t_data *all);
void	check_directory(char *bin_name, t_data *all);

int		manage_quotes(int c, int *quoted_flag);
int		is_redirect(int c);
void	skip_whitespaces(int *i, char *str);

void	unknown_arguments(int argc, char **argv);
void	check_built_ins(t_lst_d *tokens);
int		check_closed_quotes(int quoted_flag, t_data *all);

void	sig_int(int signal);
void	child_sig(int signal);
void	here_sig(int signal);

#endif
