/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:03:45 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/02 00:51:48 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	child_process_or_builtin(t_lst_d *token, t_data *all)
{
	t_token	*cur_tok;

	cur_tok = (t_token *)token->content;
	if (!cur_tok->is_built_in)
	{
		exec_cmd(cur_tok->cmd, all);
		return (-1);
	}
	else
	{
		if (exec_builtin(cur_tok, all) < 0)
			return (-1);
	}
	return (0);
}

void	do_parent_process(t_lst_d *token, int *last_exit_status, pid_t pid)
{
	close_current(token);
	if (pid > 0)
	{
		waitpid(pid, last_exit_status, 0);
		if (*last_exit_status)
			*last_exit_status = *last_exit_status >> 8;
	}
}

void	launch_cmd(t_lst_d *token, t_data *all)
{
	pid_t	pid;
	t_token	*cur_tok;

	pid = 0;
	cur_tok = (t_token *)token->content;
	if (token->next)
		if (pipe(cur_tok->pipefd))
			error_pipe_exit(token, all);
	if (!cur_tok->is_built_in)
	{
		pid = fork();
		signal(SIGINT, &child_sig);
		signal(SIGQUIT, &child_sig);
	}
	if (pid < 0)
		error_launch_exit(token, all);
	if (pid == 0 && redirect_fds(token, all) == 0)
		if (child_process_or_builtin(token, all) < 0)
			error_launch_stop(token, all);
	if (pid > 0 || cur_tok->is_built_in)
		do_parent_process(token, &(all->last_exit_status), pid);
}

void	launch_minishell(t_data *all, int num_of_tokens)
{
	t_lst_d	*tmp;

	if (num_of_tokens == 0)
		return ;
	tmp = all->tokens;
	while (tmp)
	{
		launch_cmd(tmp, all);
		all->error_exit_code = 0;
		tmp = tmp->next;
	}
}
