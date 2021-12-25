/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:30:10 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/25 21:16:09 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	get_type_of_redirect(char *line, int *i)
{
	if (line[*i] == '>')
	{
		*i += 1;
		if (line[*i] == '>')
		{
			*i += 1;
			return (DOUBLE_OUT);
		}
		return (SIMPLE_OUT);
	}
	else
	{
		*i += 1;
		if (line[*i] == '<')
		{
			*i += 1;
			return (DOUBLE_IN);
		}
		return (SIMPLE_IN);
	}
}

int	get_open_flags(int type_of_redirect)
{
	int		flags;

	if (type_of_redirect == SIMPLE_OUT || type_of_redirect == DOUBLE_OUT)
	{
		flags = O_WRONLY | O_CREAT;
		if (type_of_redirect == DOUBLE_OUT)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
	}
	else
		flags = O_RDONLY;
	return (flags);
}

char	*get_file_name(char *line, int *i)
{
	char	*name;
	int		len;
	int		quoted_flag;

	len = 0;
	quoted_flag = 0;
	while (line[*i + len] && line[*i + len] != ' ' && line[*i + len] != '|' \
											&& !(is_redirect(line[*i + len])))
	{
		if (!manage_quotes(line[*i + len], &quoted_flag))
			len += 1;
	}
	name = ft_substr(line, *i, len);
	*i += len;
	return (name);
}
