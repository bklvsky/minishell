#ifndef PARSER_H
# define PARSER_H

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

typedef struct s_token
{
	char		*cmd;
	int			fd_in;
	int			fd_out;
	int			is_built_in;
}				t_token;

/*all input:
tokens connected by*/

#endif