#include "buildins.h"

int		mini_pwd(void)
{
	char	*buffer;
	char	*error;

	buffer = NULL;
	errno = 0;
	if (!(buffer = (getcwd(buffer, PATH_MAX))))
	{
		write(2, "minishell: pwd: ", 16);
		error = strerror(errno);
		write(2, error, ft_strlen(error));
		return (errno);
	}
	else
		write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	free(buffer);
	return (0);
}
