/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:03:07 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/03 14:01:38 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	init_struct_first(t_data **all, char **env)
{
	*all = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*all)
		error_exit(*all);
	(*all)->env = ft_charmtrx_dup(env);
	if (!(*all)->env)
		error_exit(*all);
}

void	init_data(t_data *all, char *input)
{
	if (g_exit_status)
		all->last_exit_status = g_exit_status;
	g_exit_status = 0;
	(all)->tokens = new_token();
	(all)->line = input;
	if (!(all)->tokens || !(all)->line)
		error_exit(all);
}
