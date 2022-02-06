/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:39:17 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/26 22:47:02 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	env_arg_name_is_valid(char *arg, size_t name_len)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (i < name_len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_env_var(int name_len, char *name_var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name_var, env[i], name_len) == 0 && \
					(env[i][name_len] == '=' || env[i][name_len] == '\0'))
			return (i);
		i += 1;
	}
	return (-1);
}

static int	del_var(int index_to_del, char ***env)
{
	char	**tmp;
	int		i;
	int		new_i;

	tmp = (char **)ft_calloc(ft_charmtrx_len(*env), sizeof(char *));
	if (!tmp)
		return (-1);
	i = -1;
	new_i = 0;
	while ((*env)[++i])
	{
		if (i == index_to_del)
		{
			free((*env)[i]);
			continue ;
		}
		tmp[new_i] = (*env)[i];
		new_i += 1;
	}
	free(*env);
	*env = tmp;
	return (0);
}

static int	put_error_unset(char *unvalid_arg)
{
	write(2, "minishell: unset: ", 18);
	write(2, "'", 1);
	write(2, unvalid_arg, ft_strlen(unvalid_arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	ft_unset(char **args, t_data **all)
{
	int		i;
	int		env_index;
	int		exit_status;

	i = 0;
	exit_status = 0;
	while (args[i])
	{
		if (env_arg_name_is_valid(args[i], ft_strlen(args[i])))
		{
			env_index = find_env_var(ft_strlen(args[i]), args[i], (*all)->env);
			if (env_index >= 0)
				if (del_var(env_index, &(*all)->env) < 0)
					return (-1);
		}
		else
			exit_status = put_error_unset(args[i]);
		i += 1;
	}
	return (exit_status);
}
