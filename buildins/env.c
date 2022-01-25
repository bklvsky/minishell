#include "buildins.h"

int	ft_env(char **env)
{
	while(*env)
	{
		write(1, *env, ft_strlen(*env));
		write(1, "\n", 1);
		env++;
	}
	return (0);
}