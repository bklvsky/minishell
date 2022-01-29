#include "buildins.h"

int	ft_env(int fd_out, char **env)
{
	if (!fd_out)
		fd_out = 1;
	while(*env)
	{
		write(fd_out, *env, ft_strlen(*env));
		write(fd_out, "\n", 1);
		env++;
	}
	return (0);
}