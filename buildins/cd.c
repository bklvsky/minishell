#include "buildins.h"

int		error_print_return(char *message)
{
	char	*error;

	error = strerror(errno);
	write(2, "minishell: ", 11);
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (errno);
}

static int	error_cd(int mode, char *set)
{
	char	*error;

	if (mode == 1)
	{
		error = strerror(errno);
		write(2, "minishell: cd: ", 15);
		write(2, set, ft_strlen(set));
		write(2, ": ", 2);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	if (mode == 2)
		write(2, "minishell: cd: too many arguments\n", 35);
	if (mode == 3)
	{
		write(2, "minishell: cd: ", 15);
		write(2, set, ft_strlen(set));
		write(2, " not set\n", 9);
	}
	return (1);
}

static char	*get_oldpwd(char **env)
{
	char	*old_pwd;

	if (!(old_pwd = get_var_value("PWD", env)))
	{
		if (!(old_pwd = create_env_var("OLDPWD", "")))
			return (NULL);
	}
	else
	{
		if (!(old_pwd = create_env_var("OLDPWD", old_pwd)))
			return (NULL);
	}
	return (old_pwd);
}

static int	get_pwd(char **pwd)
{
	char	*error;
	char	*temp;

	*pwd = NULL;
	if (!(*pwd = getcwd(*pwd, PATH_MAX)))
	{
		error = strerror(errno);
		write(2, "minishell: cd: ", 15);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
		return (errno);
	}
	temp = *pwd;
	if (!(*pwd = create_env_var("PWD", *pwd)))
	{
		*pwd = NULL;
		free(temp);
		return (error_print_return("cd"));
	}
	free(temp);
	return (0);
}

static int	cd_to_dir(char **env, char *directory)
{
	char	*old_pwd;
	char	*pwd;
	int		err;

	errno = 0;
	if ((chdir(directory) != -1))
	{
		if (!(old_pwd = get_oldpwd(*env)))
			return (error_print_return("cd"));
		if (replace_variable(env, old_pwd))
		{
			free(old_pwd);
			return (error_print_return("cd"));
		}
		if ((err = get_pwd(&pwd)))
			return (err);
		if (replace_variable(env, pwd, 0))
		{
			free(pwd);
			return (error_print_return("cd"));
		}
	}
	else
		return (error_cd(1, directory));
	return (0);
}

int mini_cd(char **args, char **env)
{
	char  *dir;
	if (args[1] && args[2])
		return
	dir = args[1];
	if(!args[1])
		if(!(dir = get_var_value("HOME", env)))
			return (error_cd(3, "HOME"));
	if(args[1] && !ft_strncmp(args[1], "-", 2))
		if (!(dir = get_var_value("OLDPWD", env)))
			return (error_cd(3, "OLDPWD"));
	return (cd_to_dir(env, dir));
}