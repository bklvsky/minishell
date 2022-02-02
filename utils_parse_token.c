/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:39:46 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/01 16:54:18 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	get_arg_len(int quoted_flag, char *token)
{
	char	*ptr;
	int		i;

	ptr = token;
	i = 0;
	while (*ptr)
	{
		if ((*ptr == '"' && quoted_flag == DOUBLE_QUOTE) || \
		(*ptr == '\'' && quoted_flag == SINGLE_QUOTE))
			break ;
		if (((*ptr == ' ' || is_redirect(*ptr)) && !quoted_flag) || \
								(*ptr == '$' && quoted_flag != SINGLE_QUOTE))
			break ;
		i += 1;
		ptr += 1;
	}
	return (i);
}

void	make_new_cmd_arg(int *i, int *cmd_i, t_token *cur_token, t_data *all)
{
	*cmd_i += 1;
	cur_token->cmd = ft_realloc_charmtrx(cur_token->cmd, *cmd_i + 1);
	if (!cur_token->cmd)
		error_exit(all);
	skip_whitespaces(i, cur_token->token);
}
