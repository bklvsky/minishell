/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:38:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/22 02:36:04 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	put_error(t_data *all)
{
	if (all)
	{
		if (all->error_ident)
		{
			ft_putstr_fd(all->error_ident, 2);
			ft_putstr_fd(": ", 2);
		}
	}
	if (all && all->error_message)
		ft_putstr_fd(all->error_message, 2);
	else if (errno)
		ft_putstr_fd(strerror(errno), 2);
	else
		return ;
	write(2, "\n", 1);
}

void	error_syntax_exit(t_data *all)
{
	/*make it more specific: 
	for example, syntax error near unexpected token 'newline' or '|' */
	all->error_message = ft_strdup("syntax error near unexpected token");
		error_exit(all);
}

void	error_pipe_exit(t_lst_d *token, t_data *all)
{
	if (token->prev)
		close(((t_token *)token->prev->content)->pipefd[0]);
	error_exit(all);
}

void	error_launch_builtin(t_lst_d *token, t_data *all)
{
	(void)all;
	close_all(token);
}

void	error_launch_exit(t_lst_d *token, t_data *all)
{
	close_all(token);
	error_exit(all); 
}

void	error_exit(t_data *all)
{
	put_error(all);
	free_all(all);
	exit(1);
}