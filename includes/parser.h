#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/errno.h>
# include <string.h>
# include <fcntl.h>

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define SIMPLE_OUT 1
# define DOUBLE_OUT 2
# define SIMPLE_IN 3
# define DOUBLE_IN 4

typedef struct s_file
{
	char		*file_name;
	int			type_of_redirect;
}				t_file;

typedef struct s_token
{
	char		*token;
	size_t		size_of_token_line;
	char		**cmd;
	t_list		*files;
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
	char	*line;
	char	**env;
	char	*error_ident;
	char	*error_message;
}			t_data;

t_lst_d	*ft_lstdouble_new(void *elem);
void	ft_lstdouble_add_back(t_lst_d **head, t_lst_d *new);
void	ft_lstdouble_add_front(t_lst_d **head, t_lst_d *new);
t_lst_d	*ft_lstdouble_last(t_lst_d *lst);
void	ft_lstdouble_clear(t_lst_d **lst, void (*del)(void *));
void	ft_lstdouble_delone(t_lst_d *lst, void (*del)(void *));

void	init_data(t_data **all, char *line, char **env);

t_lst_d	*new_token(void);
void	parse_token(t_data *all);

void	manage_redirections(int *i, t_token *current_token, t_data *all);

int		expand_env_var(char **buf, char *source, t_data *all);
char	*get_var_name(char *line);

void	error_exit(t_data *all);
void	free_all(t_data *all);

int		manage_quotes(int c, int *quoted_flag);
int		is_redirect(int c);
void	skip_whitespaces(int *i, char *str);

#endif
