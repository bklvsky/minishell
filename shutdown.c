/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:38:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/05 17:31:56 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	error_syntax_exit(int err_index, t_lst_d *cur_token, t_data *all)
{
	all->last_exit_status = 2;
	if (all->error_message)
	{
		put_error(all);
		free(all->error_message);
		all->error_message = ft_strdup("syntax error: unexpected newline");
	}
	else
		all->error_message = get_unexpected_token(err_index, cur_token);
	if (!all->error_message)
		error_exit(all);
	put_error(all);
	close_heredocs(all->tokens);
	return (-1);
}

void	error_pipe_exit(t_lst_d *token, t_data *all)
{
	if (token->prev)
		close(((t_token *)token->prev->content)->pipefd[0]);
	error_exit(all);
}

int	error_launch_stop(t_lst_d *token, t_data *all)
{
	int		exit_code;

	if (all->error_message || all->error_ident)
		put_error(all);
	if (((t_token *)token->content)->is_built_in)
	{
		all->last_exit_status = all->error_exit_code;
		return (-1);
	}
	close_all(token);
	close_heredocs(all->tokens);
	exit_code = all->error_exit_code;
	free_all(all);
	exit(exit_code);
}

void	error_launch_exit(t_lst_d *token, t_data *all)
{
	close_all(token);
	close_heredocs(all->tokens);
	error_exit(all);
}

void	error_exit(t_data *all)
{
	int		exit_code;

	if (errno || all->error_ident || all->error_message)
		put_error(all);
	if (all)
		close_heredocs(all->tokens);
	exit_code = all->error_exit_code;
	free_all(all);
	exit(exit_code);
}
