/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:05:54 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/29 16:05:50 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

static void	check_fd_out(int *fd_out)
{
	if (!*fd_out)
		*fd_out = 1;
}

static int	check_flag(char *argument)
{
	int		index;

	index = -1;
	if (argument[++index] != '-')
		return (0);
	while (argument[++index])
		if (argument[index] != 'n')
			return (0);
	if (argument[index - 1] == '-')
		return (0);
	return (1);
}

int	ft_echo(int fd_out, char **args)
{
	int		index;
	int		flag;

	index = 0;
	flag = 0;
	check_fd_out(&fd_out);
	while (args[index])
	{
		flag = check_flag(args[index]);
		if (!flag)
			break ;
		index++;
	}
	if (index != 0)
		flag = 1;
	while (args[index])
	{
		write(fd_out, args[index], ft_strlen(args[index]));
		if (args[index + 1])
			write(fd_out, " ", 1);
		index++;
	}
	if (!flag)
		write(fd_out, "\n", 1);
	return (0);
}
