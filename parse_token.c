/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:01:12 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/02 00:33:33 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	write_in_cur_arg(int quoted_flag, char **arg, char *token, t_data *all)
{
	char	*new_line;
	char	*tmp;
	int		len_to_add;

	len_to_add = get_arg_len(quoted_flag, token);
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

int	read_token(t_token *c_tok, t_data *all)
{
	int		i;
	int		cmd_i;
	int		q_flag;

	i = 0;
	cmd_i = 0;
	q_flag = 0;
	skip_whitespaces(&i, c_tok->token);
	while (c_tok->token[i])
	{
		if (manage_quotes(c_tok->token[i], &q_flag))
			i += 1;
		else if (c_tok->token[i] == '$' && q_flag != SINGLE_QUOTE)
			i += expand_env_var(c_tok->cmd + cmd_i, c_tok->token + i, all);
		else if (!q_flag && c_tok->token[i] == ' ')
			make_new_cmd_arg(&i, &cmd_i, c_tok, all);
		else if (!is_redirect(c_tok->token[i]) || q_flag)
			i += write_in_cur_arg(q_flag, c_tok->cmd + cmd_i, \
													c_tok->token + i, all);
		else
			if (manage_redirections(&i, c_tok, all) < 0)
				return (i);
	}
	return (0);
}

int	parse_token(t_data *all)
{
	t_lst_d	*tmp;
	t_token	*cur_token;
	int		err_index;

	tmp = all->tokens;
	while (tmp)
	{
		cur_token = (t_token *)tmp->content;
		cur_token->cmd = (char **)ft_calloc(2, sizeof(char *));
		if (!cur_token->cmd)
			error_exit(all);
		if (!cur_token->token)
			return (error_syntax_exit(-1, tmp, all));
		err_index = read_token(cur_token, all);
		if (err_index)
			return (error_syntax_exit(err_index, tmp, all));
		tmp = tmp->next;
	}
	return (0);
}
