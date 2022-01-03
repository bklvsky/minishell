/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:01:12 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/04 01:56:45 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	get_arg_len(char *token)
{
	char	*ptr;
	int		i;
	
	ptr = token;
	i = 0;
	while (*ptr && *ptr != ' ' && !is_redirect(*ptr) && *ptr != '$')
	{
		i += 1;
		ptr += 1;
	}
	return (i);
}

int	write_in_current_arg(char **arg, char *token, t_data *all)
{
	char	*new_line;
	char	*tmp;
	int		len_to_add;

	len_to_add = get_arg_len(token);
	tmp = *arg;
	new_line = (char *)ft_calloc(len_to_add + 1, sizeof(char));
	if (!new_line)
		error_exit(all);
	ft_strlcpy(new_line, token, len_to_add + 1);
	*arg = ft_strjoin(tmp, new_line);
	free(tmp);
	free(new_line);
	if (!(*arg))
		error_exit(all);
	return (len_to_add);
}

/*обработать все пробельные символы
	определиться, как именно я буду везде передавать i, через ссылку или возвращать число
	а то некрасиво, что по-разному везде*/

void	read_token(t_token *cur_token, t_data *all)
{
	int		i;
	int		cmd_i;
	int		quoted_flag;

	i = 0;
	cmd_i = 0;
	quoted_flag = 0;
	if (!cur_token->token)
	{
		all->error_message = ft_strdup("syntax error");
		error_exit(all);
	}
	skip_whitespaces(&i, cur_token->token);
	while (cur_token->token[i])
	{
		if (manage_quotes(cur_token->token[i], &quoted_flag))
			i += 1;
		if (cur_token->token[i] == '$' && quoted_flag != SINGLE_QUOTE)
			i += expand_env_var(cur_token->cmd + cmd_i, cur_token->token + i, all);
		else if (!quoted_flag && cur_token->token[i] == ' ')
		{
			cmd_i += 1;
			cur_token->cmd = ft_realloc_charmtrx(cur_token->cmd, cmd_i + 1);
			if (!cur_token->cmd)
				error_exit(all);
			skip_whitespaces(&i, cur_token->token);
		}
		else if (is_redirect(cur_token->token[i]) && !quoted_flag)
			manage_redirections(&i, cur_token, all);
		else
		{
			i += write_in_current_arg(cur_token->cmd + cmd_i, cur_token->token + i, all);
		}
	}
}

void	parse_token(t_data *all)
{
	t_lst_d		*tmp;

	tmp = all->tokens;
	while (tmp)
	{
		((t_token *)(tmp->content))->cmd = (char **)ft_calloc(2, sizeof(char *));
		if (!((t_token *)(tmp->content))->cmd)
			error_exit(all);
		read_token((t_token *)tmp->content, all);
		tmp = tmp->next;
	}
}
