/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:03:54 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/27 03:14:37 by dselmy           ###   ########.fr       */
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
//# include "/Users/sstyr/.brew/Cellar/readline/8.1.1/include/readline/readline.h"
// # include "/Users/dselmy/.brew/Cellar/readline/8.1.1/include/readline/rlstd.h"
//# include "/Users/sstyr/.brew/Cellar/readline/8.1.1/include/readline/history.h"

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define SIMPLE_OUT 1
# define DOUBLE_OUT 2
# define SIMPLE_IN 3
# define DOUBLE_IN 4
# define HEREDOC_FD -2

typedef struct s_file
{
	char		*file_name;
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

typedef struct s_lst_d
{
	void			*content;
	struct s_lst_d	*prev;
	struct s_lst_d	*next;
}					t_lst_d;

typedef struct s_data
{
	t_lst_d	*tokens;
	int		last_exit_status;
	char	*line;
	char	**env;
	char	*error_ident;
	char	*error_message;
}			t_data;

# include "../buildins/buildins.h"

t_lst_d	*ft_lstdouble_new(void *elem);
void	ft_lstdouble_add_back(t_lst_d **head, t_lst_d *new);
void	ft_lstdouble_add_front(t_lst_d **head, t_lst_d *new);
t_lst_d	*ft_lstdouble_last(t_lst_d *lst);
void	ft_lstdouble_clear(t_lst_d **lst, void (*del)(void *));
void	ft_lstdouble_delone(t_lst_d *lst, void (*del)(void *));
int		ft_lstdouble_size(t_lst_d *lst);

void	init_struct_first(t_data **all, char **env);
void	init_data(t_data *all, char *input);

t_lst_d	*new_token(void);
int		parse_token(t_data *all);

int		write_in_current_arg(int quoted_flag, char **arg, char *token, t_data *all);

int		manage_redirections(int *i, t_token *current_token, t_data *all);

int		expand_env_var(char **buf, char *source, t_data *all);
char	*get_var_name(char *line);

void	error_exit(t_data *all);
void	error_pipe_exit(t_lst_d *token, t_data *all);
void	error_launch_exit(t_lst_d *token, t_data *all);
int		error_syntax_exit(int err_index, t_lst_d *cur_token, t_data *all);
void	free_all(t_data *all);
void	free_cmd(t_data *all);
void	close_all(t_lst_d *token);

int		get_open_flags(int type_of_redirect);
int		open_all_files(t_token *token, t_data *all);

void	launch_minishell(t_data *all, int num_of_tokens);
void	exec_cmd(char **cmd_args, t_data *all);
void	exec_builtin(char **cmd_args, t_data *all);
void	check_directory(char *bin_name, t_data *all);

int		manage_quotes(int c, int *quoted_flag);
int		is_redirect(int c);
void	skip_whitespaces(int *i, char *str);
void	check_built_ins(t_lst_d *tokens);

void	sig_int(int signal);
/*delete later*/

void	ft_put_read_token(void *content);
void	ft_put_tokens(void *content);

#endif
