/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 21:56:20 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/01 23:11:33 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

static int	redirect_fd_in(t_lst_d *token)
{
	t_token	*cur_tok;

	cur_tok = (t_token *)token->content;
	if (!cur_tok->is_built_in)
	{
		if (cur_tok->fd_in)
		{
			if (dup2(cur_tok->fd_in, 0) < 0)
				return (-1);
		}
		else if (token->prev)
		{
			if (dup2(((t_token *)token->prev->content)->pipefd[0], 0) < 0)
				return (-1);
		}
	}
	return (0);
}

static int	redirect_fd_out(t_lst_d *token)
{
	t_token	*cur_tok;

	cur_tok = (t_token *)token->content;
	if (cur_tok->fd_out && !cur_tok->is_built_in)
	{
		if (dup2(cur_tok->fd_out, 1) < 0)
			return (-1);
	}
	else if (token->next)
	{
		if (cur_tok->is_built_in)
			cur_tok->fd_out = cur_tok->pipefd[1];
		else if (dup2(cur_tok->pipefd[1], 1) < 0)
			return (-1);
	}
	return (0);
}

int	redirect_fds(t_lst_d *token, t_data *all)
{
	t_token	*cur_tok;

	cur_tok = (t_token *)token->content;
	if (open_all_files(cur_tok, all) < 0)
		return (error_launch_stop(token, all));
	if (redirect_fd_in(token) < 0 || redirect_fd_out(token) < 0)
		error_launch_exit(token, all);
	return (0);
}
