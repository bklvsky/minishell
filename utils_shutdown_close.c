/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shutdown_close.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:41:05 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/01 23:52:54 by dselmy           ###   ########.fr       */
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

void	close_heredocs(t_lst_d *tokens)
{
	t_lst_d	*tmp;
	t_list	*tmp_files;
	t_file	*cur_file;

	tmp = tokens;
	while (tmp && !tmp->content)
	{
		tmp_files = ((t_token *)tmp->content)->files;
		while (tmp_files && tmp_files->content)
		{
			cur_file = (t_file *)tmp_files->content;
			if (cur_file->is_heredoc && cur_file->heredoc_pipe[0] > 0)
				close(cur_file->heredoc_pipe[0]);
			tmp_files = tmp_files->next;
		}
		tmp = tmp->next;
	}
}

void	close_all(t_lst_d *token)
{
	close_current(token);
	if (token->next)
		close(((t_token *)token->content)->pipefd[0]);
}
