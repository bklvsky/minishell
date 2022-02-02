/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 02:35:01 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/01 19:41:37 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

char	*get_var_value(char *var_name, char **env)
{
	char	*env_name;
	int		i;
	char	*eq_ptr;

	i = 0;
	while (env[i])
	{
		eq_ptr = ft_strchr(env[i], '=');
		if (!eq_ptr)
			env_name = ft_strdup(env[i]);
		else
			env_name = ft_substr(env[i], 0, eq_ptr - env[i]);
		if (!env_name)
			return (NULL);
		if (!ft_strncmp(var_name, env_name, ft_strlen(var_name) + 1))
		{
			free(env_name);
			if (eq_ptr)
				return (ft_strdup(eq_ptr + 1));
			break ;
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

static char	*get_alt_var_val(char *var_name, t_data *all)
{
	if (!var_name[0])
		return (ft_strdup("$"));
	else
		return (ft_itoa(all->last_exit_status));
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
	if (!var_name[0] || ft_strncmp(var_name, "?", 2) == 0)
		var_val = get_alt_var_val(var_name, all);
	else
		var_val = get_var_value(var_name, all->env);
	free(var_name);
	if (!var_val)
		error_exit(all);
	new_line = ft_strjoin(*buf, var_val);
	free(var_val);
	if (!new_line)
		error_exit(all);
	free(*buf);
	*buf = new_line;
	return (var_name_len + 1);
}
