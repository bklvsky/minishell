/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shutdown_message.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:30:22 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/05 17:31:22 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

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

char	*get_unexpected_token(int err_index, t_lst_d *cur_token)
{
	char	*err_mes;
	char	unexp[5];
	int		i;

	if (err_index < 0 || !((t_token *)cur_token->content)->token[err_index])
	{
		if (cur_token->next)
			err_mes = ft_strdup("syntax error near unexpected token '|'");
		else
			err_mes = ft_strdup("syntax error near unexpected token 'newline'");
	}
	else
	{
		i = 0;
		unexp[i++] = '\'';
		unexp[i] = ((t_token *)cur_token->content)->token[err_index];
		if (((t_token *)cur_token->content)->token[err_index + 1] == unexp[i++])
			unexp[i++] = ((t_token *)cur_token->content)->token[err_index + 1];
		unexp[i++] = '\'';
		unexp[i] = '\0';
		err_mes = ft_strjoin("syntax error near unexpected token ", unexp);
	}
	return (err_mes);
}
