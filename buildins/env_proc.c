/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:06:21 by sstyr             #+#    #+#             */
/*   Updated: 2022/06/30 14:04:17 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include <stdio.h>

t_list	*read_env(char **strs)
{
	int		i;
	t_list	*env_list;
	t_env	*var;
	char	*equal_sign;

	env_list = NULL;
	i = 0;
	while (strs[i])
	{
		equal_sign = ft_strchr(strs[i], '=');
		var = malloc(sizeof (t_env));
		if (!var)
			exit(-1);
		var->name = ft_substr(strs[i], 0, equal_sign - strs[i]);
		if (*equal_sign != '\0')
			var->val = ft_substr(strs[i], equal_sign - strs[i], ft_strlen(strs[i]));
		else
			var->val = NULL;
		if (!var->name || (!var->val && *equal_sign != '\0'))
			exit(-1);
		ft_lstadd_back(&env_list, ft_lstnew(var));
		i++;
	}
	return (env_list);
}


t_env	*get_var_by_name(t_list *env_list, char *name)
{
	t_list	*tmp;
	t_env	*var;

	tmp = env_list;
	while (tmp)
	{
		var = tmp->content;
		if (ft_strncmp(var->name, name, ft_strlen(name)) == 0)
		{
			return (var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_val_by_name(t_list *env_list, char *name)
{
	t_list	*tmp;
	t_env	*var;

	tmp = env_list;
	while (tmp)
	{
		var = tmp->content;
		if (ft_strncmp(var->name, name, ft_strlen(var->name)) == 0)
			return (var->val);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*change_var_val(t_list **env_list, char *name, char *new_val)
{
	t_env	*var;

	var = get_var_by_name(*env_list, name);
	if (!var)
	{
		var = malloc(sizeof(t_env));
		var->name = ft_strdup(name);
		var->val = ft_strdup(new_val);
		ft_lstadd_back(env_list, ft_lstnew(var));
	}
	else
	{
		free(var->val);
		var->val = ft_strdup(new_val);
	}
	return (var->val);
}
