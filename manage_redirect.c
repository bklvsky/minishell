/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:30:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/03 15:31:44 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	get_file_name(char *line, int *i, t_file *file_data, t_data *all)
{
	int		q_flag;
	int		j;

	q_flag = 0;
	j = *i;
	while (line[j])
	{
		if (!q_flag && (line[j] == ' ' || is_redirect(line[j])))
			break ;
		else if (manage_quotes(line[j], &q_flag))
			j += 1;
		else if (line[j] == '$' && q_flag != SINGLE_QUOTE \
								&& file_data->type_of_redirect != DOUBLE_IN)
			j += expand_env_var(&(file_data->name), line + j, all);
		else
			j += write_in_cur_arg(q_flag, &(file_data->name), line + j, all);
	}
	if (!file_data->name || !file_data->name[0])
	{
		file_data->name = ft_substr(line, *i, j - *i);
		if (!file_data)
			error_exit(all);
		file_data->ambiguous_redir = 1;
	}
	*i = j;
}

void	get_heredoc_process(t_file *file_data, t_data *all)
{
	char	*input;
	int		delim_len;

	delim_len = ft_strlen(file_data->name);
	close(file_data->heredoc_pipe[0]);
	stop_here_loop = 1;
	while (stop_here_loop)
	{
		input = readline("> ");
		if (!input || ft_strncmp(input, file_data->name, delim_len + 1) == 0)
			break ;
		write(file_data->heredoc_pipe[1], input, ft_strlen(input));
		write(file_data->heredoc_pipe[1], "\n", 1);
		free(input);
	}
	if (!input)
		printf("minishell: warning: here-document delimited \
by end-of-file (wanted '%s')\n", file_data->name);
	free(input);
	close(file_data->heredoc_pipe[1]);
	close_heredocs(all->tokens);
	free_all(all);
	exit(0);
}

int	get_heredoc(t_file	*file_data, t_data *all)
{
	pid_t	pid;
	int		exit_status;

	file_data->is_heredoc = 1;
	if (pipe(file_data->heredoc_pipe))
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	signal(SIGINT, &here_sig);
	if (pid < 0)
		return (-1);
	if (pid == 0)
		get_heredoc_process(file_data, all);
	else
	{
		waitpid(pid, &exit_status, 0);
		close(file_data->heredoc_pipe[1]);
		if (exit_status)
			all->interrupted = 1;
	}
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
	if ((!new_file->name || !new_file->name[0]) && !flag_env_var)
		return (-1);
	if (new_file->type_of_redirect == DOUBLE_IN)
		if (get_heredoc(new_file, all) < 0)
			error_exit(all);
	return (all->interrupted);
}
