/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_proc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:06:10 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/16 20:06:12 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	del_env(void *content)
{
	t_env	*var;

	var = content;
	free(var->name);
	free(var->val);
	free(var);
}

void	clear_env(t_list **env_list)
{
	ft_lstclear(env_list, del_env);
}

char	*env_to_strs_sub(char *name, char *val)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(name, "=");
	res = ft_strjoin(tmp, val);
	free(tmp);
	return (res);
}

char	**env_to_strs(t_list **env_list)
{
	t_list	*tmp;
	t_env	*var;
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(*env_list) + 1));
	i = 0;
	tmp = *env_list;
	while (tmp->next)
	{
		var = tmp->content;
		res[i] = env_to_strs_sub(var->name, var->val);
		i++;
		tmp = tmp->next;
	}
	var = tmp->content;
	res[i] = env_to_strs_sub(var->name, var->val);
	i++;
	res[i] = NULL;
	return (res);
}

int	error_print_return(char *message)
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
