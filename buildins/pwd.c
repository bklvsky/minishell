/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:06:28 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/25 23:09:39 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	ft_pwd(t_data *all)
{
	char	*buffer;
	//char	*error;

	buffer = NULL;
	errno = 0;
	buffer = getcwd(buffer, PATH_MAX);
	if (!buffer)
	{
		write(2, "minishell: pwd: ", 16);
		all->error_ident = ft_strdup("pwd");
		//write(2, error, ft_strlen(error));
		return (errno);
	}
	else
		write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	free(buffer);
	return (0);
}
