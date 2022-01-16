/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:06:28 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/16 20:06:29 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	ft_pwd(void)
{
	char	*buffer;
	char	*error;

	buffer = NULL;
	errno = 0;
	buffer = getcwd(buffer, PATH_MAX);
	if (!buffer)
	{
		write(2, "minishell: pwd: ", 16);
		error = strerror(errno);
		write(2, error, ft_strlen(error));
		return (errno);
	}
	else
		write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	free(buffer);
	return (0);
}
