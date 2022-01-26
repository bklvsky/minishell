/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 01:40:59 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/26 22:47:15 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

static void	put_sort_env(char **env)
{
	char	**sort_env;

	sort_env = ft_charmtrx_dup(env);
	sort_environ(sort_env, 0, ft_charmtrx_len(sort_env) - 1);
	export_env(sort_env);
	ft_free_charmtrx(sort_env);
}

int	rewrite_env_var(int env_index, char *arg, char **env)
{
	char	*tmp;

	tmp = env[env_index];
	if (ft_strchr(arg, '='))
	{
		env[env_index] = ft_strdup(arg);
		free(tmp);
		if (!env[env_index])
			return (-1);
	}
	return (0);
}

int	add_env_var(char *arg, char ***env)
{
	char	*arg_to_write;

	arg_to_write = ft_strdup(arg);
	if (!arg_to_write)
		return (-1);
	*env = ft_realloc_charmtrx(*env, ft_charmtrx_len(*env) + 1);
	if (!*env)
		return (-1);
	(*env)[ft_charmtrx_len(*env)] = arg_to_write;
	return (0);
}

int	write_var_in_env(char *arg, char ***env)
{
	char	*eq_ptr;
	int		env_index;
	size_t	name_len;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr)
		name_len = eq_ptr - arg;
	else
		name_len = ft_strlen(arg);
	env_index = find_env_var(name_len, arg, *env);
	if (env_index > 0)
		rewrite_env_var(env_index, arg, *env);
	else
		add_env_var(arg, env);
	return (0);
}

int	ft_export(char **args, t_data **all)
{
	int		i;
	char	*eq_ptr;
	size_t	name_len;

	if (!args[0])
		put_sort_env((*all)->env);
	i = 0;
	while (args[i])
	{
		eq_ptr = ft_strchr(args[i], '=');
		if (!eq_ptr)
			name_len = ft_strlen(args[i]);
		else
			name_len = eq_ptr - args[i];
		if (env_arg_name_is_valid(args[i], name_len))
			write_var_in_env(args[i], &(*all)->env);
		else
			put_error_export(args[i]);
		i += 1;
	}
	return (0);
}
