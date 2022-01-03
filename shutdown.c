/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:38:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/02 19:01:01 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	free_file(void *ptr)
{
	t_file	*file;

	file = (t_file *)ptr;
	free(file->file_name);
	free(ptr);
}

void	free_token(void *ptr)
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
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	else if (all && all->error_message)
		ft_putstr_fd(all->error_message, 2);
	else
		return ;
	write(2, "\n", 1);
}

void	error_exit(t_data *all)
{
	put_error(all);
	free_all(all);
	exit(1);
}