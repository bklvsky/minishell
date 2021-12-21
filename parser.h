#ifndef PARSER_H
# define PARSER_H

typedef struct s_parse
{
	int			single_quoted;
	int			double_quoted;
	int			backslash;
}				t_parse;

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