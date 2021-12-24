/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:01:12 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/24 20:08:38 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	read_token(t_token *current_token, t_data *all)
{
	int		i;
	int		quoted_flag;

	i = -1;
	quoted_flag = 0;
	while (current_token->token[++i])
	{
		manage_quotes(current_token->token[i], &quoted_flag);
		if (current_token->token[i] == '$' && quoted_flag != SINGLE_QUOTE)
			expand_env_variable(current_token, all);
		if (is_redirect(current_token->token[i]))
			manage_redirect();
	}
}

int		management(t_token *current_token, char *line, t_data *all)
{
	if (*line == '>')
	{
		*line = ' ';
		line += 1;
		if (*line) == '>'
			append_mode();
	}
	else if (*line ==)
	{

	}
}

void	manage_redirect(t_token *current_token, t_data *all)
{
	int		i;
	int		quoted_flag;

	i = -1;
	quoted_flag = 0;
	while (current_token->token[++i])
	{
		manage_quotes(current_token->token[i], &quoted_flag);
		if (is_redirect(current_token->token[i]) && !quoted_flag)
			if (!management())
				error_exit(all);
	}
}

void	parse_token(t_data *all)
{
	t_lst_d		*tmp;

	tmp = all->tokens;
	while (tmp)
	{
		read_token((t_token *)tmp->content, all);
		tmp = tmp->next;
	}
}