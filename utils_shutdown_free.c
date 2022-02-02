/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shutdown_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 19:49:24 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/02 00:21:08 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

static void	free_file(void *ptr)
{
	t_file	*file;

	file = (t_file *)ptr;
	free(file->name);
	free(ptr);
}

static void	free_token(void *ptr)
{
	t_token		*token;

	token = (t_token *)ptr;
	if (token)
	{
		free(token->token);
		ft_free_charmtrx(token->cmd);
		ft_lstclear(&(token->files), &free_file);
		free(token);
	}
}

void	free_cmd(t_data *all)
{
	if (all)
	{
		free(all->error_ident);
		all->error_ident = NULL;
		free(all->error_message);
		all->error_message = NULL;
		free(all->line);
		all->line = NULL;
		ft_lstdouble_clear(&(all->tokens), &free_token);
		all->tokens = NULL;
	}
}

void	free_all(t_data *all)
{
	if (all)
	{
		ft_free_charmtrx(all->env);
		free(all->line);
		ft_lstdouble_clear(&(all->tokens), &free_token);
		free(all->error_ident);
		free(all->error_message);
		free(all);
	}
}
