/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shutdown.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:41:05 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/28 03:58:16 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

static void	close_file_fds(t_token *token_data)
{
	if (token_data->fd_in > 0)
		close(token_data->fd_in);
	if (token_data->fd_out > 0)
		close(token_data->fd_out);
}

void	close_current(t_lst_d *token)
{
	t_token	*token_data;

	token_data = (t_token *)token->content;
	close_file_fds(token_data);
	if (token->prev)
		close(((t_token *)token->prev->content)->pipefd[0]);
	if (token->next)
		close(token_data->pipefd[1]);
}

void	close_all(t_lst_d *token)
{
	close_current(token);
	if (token->next)
		close(((t_token *)token->content)->pipefd[0]);
}

static void	free_file(void *ptr)
{
	t_file	*file;

	file = (t_file *)ptr;
	free(file->file_name);
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