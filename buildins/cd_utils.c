/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:27:59 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/17 14:28:00 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	check_env_free(t_list **env_list, char ***env)
{
	static char	**old_env = NULL;
	int			i;

	i = 0;
	if (!old_env)
		*env = env_to_strs(env_list);
	else
	{
		while (*(old_env + i))
		{
			free(*(old_env + i));
			i++;
		}
		free(old_env);
	}
	old_env = *env;
}
