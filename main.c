/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:06:48 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/02 00:26:53 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*all;
	char	*inpt;

	rl_catch_signals = 0;
	g_exit_status = 0;
	if (argc == 1)
	{
		init_struct_first(&all, envp);
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &sig_int);
			inpt = readline("minishell: ");
			init_data(all, inpt);
			if (*inpt)
			{
				add_history(inpt);
				if (!parser(all))
					launch_minishell(all, ft_lstdouble_size(all->tokens));
			}
			free_cmd(all);
		}
	}
	unknown_arguments(argc, argv);
	return (0);
}
