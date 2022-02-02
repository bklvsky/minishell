/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:41:42 by sstyr             #+#    #+#             */
/*   Updated: 2022/02/02 17:41:45 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	ft_env(int fd_out, char **env)
{
	char	**strs;

	strs = NULL;
	if (!fd_out)
		fd_out = 1;
	while (*env)
	{
		strs = ft_split(*env, '=');
		if (strs[1])
		{
			write(fd_out, *env, ft_strlen(*env));
			write(fd_out, "\n", 1);
		}
		free(strs[0]);
		free(strs[1]);
		free(strs);
		env++;
	}
	return (0);
}
