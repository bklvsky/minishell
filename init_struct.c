/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:03:07 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/17 19:11:50 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	init_struct_first(t_data **all, char **env)
{
	*all = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*all)
		error_exit(*all);
//	(*all)->tokens = new_token();
	(*all)->env = ft_charmtrx_dup(env);
//	(*all)->line = line;
	if (!(*all)->env)
		error_exit(*all);
}

void	init_data(t_data *all, char *input)
{
	(all)->tokens = new_token();
	(all)->line = input;
	if (!(all)->tokens || !(all)->line)
		error_exit(all);
}
