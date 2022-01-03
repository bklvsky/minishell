/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:10:22 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/04 00:53:35 by dselmy           ###   ########.fr       */
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
