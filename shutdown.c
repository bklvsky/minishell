/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:38:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/27 04:58:33 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

/*
	possible scenarios of shutdowns:
	1. from parser
		(files not open, pipes for heredocs, pipes between processes not open)
	2. from launcher
		2.1 error pipe or dup
	3. from child proccess
		just clean everything, heredocs are already closed, the last one in fdin
*/

void	put_error(t_data *all)
{
	ft_putstr_fd("minishell: ", 2);
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

void	close_heredocs(t_lst_d *tokens)
{
	t_lst_d	*tmp;
	t_list	*tmp_files;

	tmp = tokens;
	while (tmp && !tmp->content)
	{
		tmp_files = ((t_token *)tmp->content)->files;
		while (tmp_files && tmp_files->content)
		{
			if (((t_file *)tmp_files->content)->is_heredoc)
				close(((t_file *)tmp_files->content)->heredoc_pipe[1]);
			tmp_files = tmp_files->next;
		}
		tmp = tmp->next;
	}
}

static char	*get_unexpected_token(int err_index, t_lst_d *cur_token)
{
	char	*err_mess;
	char	unexp[5];
	int		i;
	
	if (err_index < 0 || !((t_token *)cur_token->content)->token[err_index])
	{
		if (cur_token->next)
			err_mess = ft_strdup("syntax error near unexpected token '|'");
		else
			err_mess = ft_strdup("syntax error near unexpected token 'newline'");
	}
	else
	{
		i = 0;
		unexp[i++] = '\'';
		unexp[i] = ((t_token *)cur_token->content)->token[err_index];
		if (((t_token *)cur_token->content)->token[err_index + 1] == unexp[i++])
			unexp[i++] = ((t_token *)cur_token->content)->token[err_index + 1];
		unexp[i++]='\'';
		unexp[i] = '\0';
		err_mess = ft_strjoin("syntax error near unexpected token ", unexp);
	}
	return (err_mess);
}

int	error_syntax_exit(int err_index, t_lst_d *cur_token, t_data *all)
{
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
	if (all)
		close_heredocs(all->tokens);
	free_all(all);
	exit(127);
}