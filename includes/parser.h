#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdio.h>

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define PIPE_BACK 1
# define PIPE_FRONT 2

typedef struct s_token
{
	char		*line;
	char		**cmd;
	int			fd_in;
	int			fd_out;
	int			is_built_in;
	int			pipe_link;
}				t_token;

/*all input:
tokens connected by*/

#endif