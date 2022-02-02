/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:06:21 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/16 20:06:22 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include <stdio.h>

t_list	*read_env(char **strs)
{
	int		i;
	t_list	*env_list;
	t_env	*var;
	char	**tmp;

	env_list = NULL;
	i = 0;
	while (strs[i])
	{
		tmp = ft_split(strs[i], '=');
		var = malloc(sizeof (t_env));
		var->name = ft_strdup(tmp[0]);
		var->val = ft_strdup(tmp[1]);
		ft_lstadd_back(&env_list, ft_lstnew(var));
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(tmp - 2);
		i++;
	}
	return (env_list);
}

void	print_env(t_list **env_list)
{
	t_list	*tmp;
	t_env	*var;

	tmp = NULL;
	if (*env_list)
		tmp = *env_list;
	while (tmp->next)
	{
		var = tmp->content;
		printf("%s = %s\n", var->name, var->val);
		tmp = tmp->next;
	}
}

t_env	*get_var_by_name(t_list **env_list, char *name)
{
	t_list	*tmp;
	t_env	*var;

	tmp = NULL;
	if (*env_list)
		tmp = *env_list;
	while (tmp->next)
	{
		var = tmp->content;
		if (ft_strncmp(var->name, name, ft_strlen(name)) == 0)
			return (var);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_val_by_name(t_list **env_list, char *name)
{
	t_list	*tmp;
	t_env	*var;

	tmp = NULL;
	if (*env_list)
		tmp = *env_list;
	while (tmp->next)
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

	var = get_var_by_name(env_list, name);
	if (var)
	{
		free(var->val);
		var->val = ft_strdup(new_val);
	}
	else
	{
		var = malloc(sizeof(t_env));
		var->name = ft_strdup(name);
		var->val = ft_strdup(new_val);
	}
	return (var->val);
}
