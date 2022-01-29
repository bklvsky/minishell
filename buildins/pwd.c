/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:06:28 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/29 16:06:17 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	ft_pwd(int fd_out, t_data *all)
{
	char	*buffer;
	//char	*error;

	buffer = NULL;
	errno = 0;
	buffer = getcwd(buffer, PATH_MAX);
	if (!fd_out)
		fd_out = 1;
	if (!buffer)
	{
		write(2, "minishell: pwd: ", 16);
		all->error_ident = ft_strdup("pwd");
		//write(2, error, ft_strlen(error));
		return (errno);
	}
	else
		write(fd_out, buffer, ft_strlen(buffer));
	write(fd_out, "\n", 1);
	free(buffer);
	return (0);
}

