/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 02:35:01 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/16 20:01:16 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

/*check for permitted symbols is alnum || '_' (is digit not in the first symbol)
if '?' ->last exit status*/

char	*get_var_value(char *var_name, char **env)
{
	char	*env_name;
	int		i;

	i = 0;
	if (!var_name[0])
		return (ft_strdup("$"));
	while (env[i])
	{
		env_name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (!env_name)
			return (NULL);
		if (!ft_strncmp(var_name, env_name, ft_strlen(var_name) + 1))
		{
			free(env_name);
			return (ft_strdup(ft_strchr(env[i], '=') + 1));
		}
		free(env_name);
		i++;
	}
	return (ft_strdup(""));
}

char	*get_var_name(char *line)
{
	int		len_of_name;
	char	*ptr;

	ptr = line;
	len_of_name = 0;
	if (*ptr == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(*ptr) && *ptr != '_')
		return (ft_strdup(""));
	while (ft_isalnum(*ptr) || *ptr == '_')
	{
		len_of_name += 1;
		ptr++;
	}
	return (ft_substr(line, 0, len_of_name));
}

int	expand_env_var(char **buf, char *source, t_data *all)
{
	char		*var_name;
	char		*var_val;
	char		*new_line;
	int			var_name_len;

	var_name = get_var_name(source + 1);
	if (!var_name)
		error_exit(all);
	var_name_len = ft_strlen(var_name);
	if (ft_strncmp(var_name, "?", 2) == 0)
		var_val = ft_itoa(all->last_exit_status);
	else
		var_val = get_var_value(var_name, all->env);
	if (!var_val)
	{
		free(var_name);
		error_exit(all);
	}
	new_line = ft_strjoin(*buf, var_val);
	free(var_name);
	free(var_val);
	if (!new_line)
		error_exit(all);
	free(*buf);
	*buf = new_line;
	return (var_name_len + 1);
}