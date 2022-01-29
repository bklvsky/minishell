/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:30:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/29 15:43:36 by dselmy           ###   ########.fr       */
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

void	get_file_name(char *line, int *i, t_file *file_data, t_data *all)
{
	int		quoted_flag;
	int		j;
	
	quoted_flag = 0;
	j = *i;
	while (line[j])
	{
		if (!quoted_flag && (line[j] == ' ' || is_redirect(line[j])))
			break ;
		else if (manage_quotes(line[j], &quoted_flag))
			j += 1;
		else if (line[j] == '$' && quoted_flag != SINGLE_QUOTE \
								&& file_data->type_of_redirect != DOUBLE_IN)
			j += expand_env_var(&(file_data->file_name), line + j, all);
		else
			j += write_in_current_arg(quoted_flag, &(file_data->file_name), line + j, all);
	}
	if (!file_data->file_name || !file_data->file_name[0])
	{
		file_data->file_name = ft_substr(line, *i, j - *i);
		if (!file_data)
			error_exit(all);
		file_data->ambiguous_redir = 1;
	}
	*i = j;
}

int	get_heredoc(t_file	*file_data)
{
	char	*input;
	int		delimeter_len;

	file_data->is_heredoc = 1;
	delimeter_len = ft_strlen(file_data->file_name);
	if (pipe(file_data->heredoc_pipe))
		return (-1);
	input = readline("> ");
	signal(SIGINT, &here_sig);
	while (input && ft_strncmp(input, file_data->file_name, delimeter_len + 1))
	{
		write(file_data->heredoc_pipe[1], input, ft_strlen(input));
		write(file_data->heredoc_pipe[1], "\n", 1);
		free(input);
		input = readline("> ");
	}
	if (!input)
		printf("minishell: warning: here-document delimited \
by end-of-file (wanted '%s')\n", file_data->file_name);
	close(file_data->heredoc_pipe[1]);
	free(input);
	return (0);
}

int	add_new_file(t_file **new_file, t_list **head_files)
{
	t_list	*new_lst;
	
	*new_file = (t_file *)ft_calloc(1, sizeof(t_file));
	if (!*new_file)
		return (-1);
	new_lst = ft_lstnew(*new_file);
	if (!new_lst)
	{
		free(*new_file);
		return (-1);
	}
	ft_lstadd_back(head_files, new_lst);
	return (0);
}

int	manage_redirections(int *i, t_token *cur_token, t_data *all)
{
	t_file	*new_file;
	int		flag_env_var;

	flag_env_var = 0;
	if (add_new_file(&new_file, &(cur_token->files)) < 0)
		error_exit(all);
	new_file->type_of_redirect = get_type_of_redirect(cur_token->token, i);
	skip_whitespaces(i, cur_token->token);
	if ((cur_token->token)[*i] == '$')
		flag_env_var = 1;
	get_file_name(cur_token->token, i, new_file, all);
	skip_whitespaces(i, cur_token->token);
	if ((!new_file->file_name || !new_file->file_name[0]) && !flag_env_var)
		return (-1);// not exit but free_cmd and back to cycle
	if (new_file->type_of_redirect == DOUBLE_IN)
		get_heredoc(new_file); //check_for_pipe_error
	return (0);
}
