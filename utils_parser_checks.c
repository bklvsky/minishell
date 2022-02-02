/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:42:42 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/02 00:44:36 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	unknown_arguments(int argc, char **argv)
{
	int		i;

	i = 0;
	write(2, "minishell: unknown arguments: ", 30);
	while (++i < argc)
	{
		write(2, "\"", 1);
		write(2, argv[i], ft_strlen(argv[i]));
		write(2, "\"", 1);
		if (i + 1 < argc)
			write(2, ", ", 2);
	}
	write(2, "\nUsage: ./minishell [--no arguments]\n", 37);
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
	t_lst_d	*tmp;
	t_token	*token_data;

	tmp = tokens;
	while (tmp)
	{
		token_data = (t_token *)tmp->content;
		if (token_data->cmd[0])
		{
			if (is_builtin(token_data->cmd[0]))
				token_data->is_built_in = 1;
		}
		tmp = tmp->next;
	}
}

int	check_closed_quotes(int quoted_flag, t_data *all)
{
	if (quoted_flag)
	{
		if (quoted_flag == SINGLE_QUOTE)
			all->error_message = ft_strdup("unexpected newline \
while looking for matching '''");
		else
			all->error_message = ft_strdup("unexpected newline \
while looking for matching '\"'");
		return (error_syntax_exit(0, NULL, all));
	}
	return (0);
}
