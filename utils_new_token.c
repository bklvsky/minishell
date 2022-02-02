/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:29:40 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/01 16:30:34 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

t_lst_d	*new_token(void)
{
	t_token		*new_token;
	t_lst_d		*new_lst;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_lst = ft_lstdouble_new(new_token);
	if (!new_lst)
	{
		free(new_token);
		return (NULL);
	}
	return (new_lst);
}

void	new_pipe_token(t_data *all)
{
	t_lst_d		*new;

	new = new_token();
	if (!new)
		error_exit(all);
	ft_lstdouble_add_back(&(all->tokens), new);
}
