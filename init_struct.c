/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:03:07 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/23 21:05:09 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	init_data(t_data **all, char *line, char **env)
{
	*all = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*all)
		error_exit(*all);
	(*all)->tokens = new_token();
	(*all)->env = ft_charmtrx_dup(env);
	(*all)->line = ft_strdup(line);
	if (!(*all)->env || !(*all)->env || !(*all)->tokens)
		error_exit(*all);
}
