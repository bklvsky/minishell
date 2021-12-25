/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:01:12 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/25 21:16:12 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	manage_redirections(int *i, t_token *cur_token, t_data *all)
{
	t_file	new_file;
	int		open_flags;

	new_file.type_of_redirect = get_type_of_redirect(all->line, i);
//	open_flags = get_open_flags(new_file.type_of_redirect);
	skip_whitespaces(i, all->line);
	new_file.file_name = get_file_name(all->line, i);
	if (!new_file.file_name || !new_file.file_name[0])
	{
		all->error_message = ft_strdup("syntax error near unexpected token");
		free(new_file.file_name);
		error_exit(all);
	}
/*	if (new_file.type_of_redirect == SIMPLE_OUT || type_of_redirect == DOUBLE_OUT)
		cur_token->fd_out = open(file_name, open_flags, 00644);
	else
		cur_token->fd_in = open(file_name, open_flags);
	if (errno)
	{
		all->error_ident = file_name;
		error_exit(all);
	}*/
//	printf("file name = %s\n", file_name);
}

//void	go_to_next_cmd_arg()

void	expand_env_var(char *buf, char *line, t_data *all)
{
	size_t		old_size;

	if (!buf)
		old_size = ft_strchr(line, ' ') - line;
	else
		old_size = ft_strlen(buf);
	/*find the variable in all->env, count its size, add this size to the old one
		strrealloc old buf with new size and write the variable in the buf*/
}

void	read_token(t_token *cur_token, t_data *all)
{
	int		i;
	int		cmd_i;
	int		quoted_flag;

	i = -1;
	cmd_i = 0;
	quoted_flag = 0;
	while (cur_token->token[++i])
	{
		if (manage_quotes(cur_token->token[i], &quoted_flag))
			continue ;
		if (cur_token->token[i] == '$' && quoted_flag != SINGLE_QUOTE)
			expand_env_var(cur_token->cmd[cmd_i], cur_token->token + i, all);
		else if (!quoted_flag && cur_token->token[i] == ' ')
		{
			ft_realloc_charmtrx(cur_token->cmd, cmd_i);
			cmd_i += 1;
			skip_whitespaces(&i, cur_token->token + i);
		}
		else if (is_redirect(cur_token->token[i]) && !quoted_flag)
			manage_redirections();
		else
			write_in_current_arg();
	}
}

void	parse_token(t_data *all)
{
	t_lst_d		*tmp;

	tmp = all->tokens;
	while (tmp)
	{
		(t_token *)(tmp->content)->cmd = (char **)ft_calloc(1, sizeof(char *));
		if (!(t_token *)(tmp->content)->cmd)
			error_exit(all);
		read_token((t_token *)tmp->content, all);
		tmp = tmp->next;
	}
}
