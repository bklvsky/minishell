/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:45:15 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/03 15:16:57 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

static int	write_in_token(t_token *token, char c)
{
	size_t	i;

	if (!token->token)
	{
		token->token = (char *)ft_calloc(256, sizeof(char));
		if (!token)
			return (-1);
		token->size_of_token_line = 256;
	}
	i = ft_strlen(token->token);
	if (i == token->size_of_token_line - 1)
	{
		token->size_of_token_line *= 2;
		token->token = ft_strrealloc(token->token, token->size_of_token_line);
		if (!token->token)
			return (-1);
	}
	token->token[i] = c;
	return (0);
}

static int	recognise_tokens(t_data *all)
{
	int			quoted_flag;
	int			i;
	t_lst_d		*tmp;

	i = -1;
	quoted_flag = 0;
	tmp = all->tokens;
	while (all->line[++i])
	{
		manage_quotes(all->line[i], &quoted_flag);
		if (all->line[i] != '|' || quoted_flag)
		{
			if (write_in_token((t_token *)tmp->content, all->line[i]) < 0)
				error_exit(all);
		}
		else
		{
			new_pipe_token(all);
			tmp = tmp->next;
		}
	}
	return (check_closed_quotes(quoted_flag, all));
}

int	parser(t_data *all)
{
	if (recognise_tokens(all) < 0)
		return (-1);
	if (parse_token(all))
		return (-1);
	check_built_ins(all->tokens);
	return (0);
}
