/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:05:40 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/16 20:05:43 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

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

static char	*get_oldpwd(t_list *env)
{
	char	*old_pwd;

	old_pwd = get_val_by_name(&env, "PWD");
	if (old_pwd)
	{
		old_pwd = change_var_val(&env, "OLDPWD", old_pwd);
		if (!old_pwd)
			return (NULL);
	}
	return (old_pwd);
}

static int	get_pwd(char **pwd, t_list *env)
{
	char	*error;
	char	*temp;

	*pwd = NULL;
	*pwd = getcwd(*pwd, PATH_MAX);
	if (!(*pwd))
	{
		error = strerror(errno);
		write(2, "minishell: cd: ", 15);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
		return (errno);
	}
	temp = *pwd;
	*pwd = change_var_val(&env, "PWD", *pwd);
	if (!(*pwd))
	{
		*pwd = NULL;
		free(temp);
		return (error_print_return("cd"));
	}
	free(temp);
	return (0);
}

static int	cd_to_dir(t_list *env, char *directory)
{
	char	*old_pwd;
	char	*pwd;
	int		err;

	errno = 0;
	if ((chdir(directory) != -1))
	{
		old_pwd = get_oldpwd(env);
		if (!old_pwd)
			return (error_print_return("cd"));
		err = get_pwd(&pwd, env);
		if (err)
			return (err);
	}
	else
		return (error_cd(1, directory));
	return (0);
}

int	ft_cd(char **args, char ***env)
{
	char		*dir;
	t_list		*env_list;
	int			res;

	env_list = read_env(*env);
	dir = args[0];
	if (!args[0])
	{
		dir = get_val_by_name(&env_list, "HOME");
		if (!dir)
			return (error_cd(3, "HOME"));
	}
	if (args[0] && !ft_strncmp(args[0], "-", 2))
	{
		dir = get_val_by_name(&env_list, "OLDPWD");
		if (!dir)
			return (error_cd(3, "OLDPWD"));
	}
	res = cd_to_dir(env_list, dir);
	ft_free_charmtrx(*env);
	*env = env_to_strs(&env_list);
	clear_env(&env_list);
	return (res);
}
