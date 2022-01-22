/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:10:22 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/22 02:37:32 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_redirect(int c)
{
	return (c =='>' || c =='<');
}

int	manage_quotes(int c, int *quoted_flag)
{
	if (c == '\'' && !(*quoted_flag))
		*quoted_flag = SINGLE_QUOTE;
	else if (c == '"' && !(*quoted_flag))
		*quoted_flag = DOUBLE_QUOTE;
	else if ((c == '\'' && *quoted_flag == SINGLE_QUOTE) || \
									(c == '"' && *quoted_flag == DOUBLE_QUOTE))
		*quoted_flag = 0;
	else
		return (0);
	return (1);
}

void	skip_whitespaces(int *i, char *str)
{
	while (str[*i] == ' ')
		*i += 1;
}

static int	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 5) | !ft_strncmp(cmd, "cd", 3) | \
	!ft_strncmp(cmd, "pwd", 4) | !ft_strncmp(cmd, "export", 7) | \
	!ft_strncmp(cmd, "unset", 6) | !ft_strncmp(cmd, "env", 4) | \
	!ft_strncmp(cmd, "exit", 4));
}

void	check_built_ins(t_lst_d *tokens)
{
	t_lst_d *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (is_builtin(((t_token *)tmp->content)->cmd[0]))
			((t_token *)tmp->content)->is_built_in = 1;
		tmp = tmp->next;
	}
}