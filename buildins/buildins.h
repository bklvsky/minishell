#ifndef BUILDINS_H
#define BUILDINS_H

# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char 			*name;
	char 			*val;
}					t_env;

int		mini_echo(char **args);

t_list	*read_env(char **strs);
void	print_env(t_list **env_list);
t_env  *get_env_by_name(t_list **env_list, char *name);
#endif
