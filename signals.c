/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:05:40 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/16 20:05:43 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

void	sig_int(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	here_sig(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		exit(0);
	}
}

void	child_sig(int signal)
{
	if (signal == SIGINT)
	{
		(void)signal;
		write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		(void)signal;
		write(2, "Quit: 3\n", 8);
	}
}
