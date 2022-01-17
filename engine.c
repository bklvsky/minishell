/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:03:45 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/17 20:12:26 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

/*i need to create a pipe from the main process that will work in cases of
builtins, and in case of heredocs
builtins should not be a forked process 100% or the changes to t_data *all 
would remain exclusively in this child process*/

void	redirect_fds(t_lst_d *token, t_data *all)
{
	t_token	*token_data;

	token_data = (t_token *)token->content;
	if (open_all_files(token_data, all) < 0)
		error_launch_exit(token, all);
	if (token_data->fd_in)
	{
		if (token_data->fd_in != HEREDOC_FD)
			if (dup2(token_data->fd_in, 0) < 0)
				error_launch_exit(token, all);
	}
	else if (token->prev && \
				dup2(((t_token *)token->prev->content)->pipefd[0], 0) < 0)
		error_launch_exit(token, all);
	if (token_data->fd_out)
	{
		if (dup2(token_data->fd_out, 1) < 0)
			error_launch_exit(token, all);
	}
	else if (token->next && dup2(token_data->pipefd[1], 1) < 0)
		error_launch_exit(token, all);
}

void	launch_cmd(t_lst_d *token, t_data *all)
{
	pid_t	pid;
	t_token	*token_data;

	token_data = (t_token *)token->content;
	if (token->next)
		if (pipe(token_data->pipefd))
			error_pipe_exit(token, all);
	pid = fork();
	if (pid < 0)
		error_launch_exit(token, all);
	else if (pid == 0)
	{
		redirect_fds(token, all);
	//	if (token->next)
	//		close(token_data->fd[0]);//not sure if i need it really or exec will close it
		exec_cmd(token_data->cmd, all);
		error_launch_exit(token, all);
	}
	else
	{
		if (token->prev)
			close(((t_token *)token->prev->content)->pipefd[0]);
		if (token->next)
			close(token_data->pipefd[1]);
		waitpid(pid, &all->last_exit_status, 0);
	}
}

void	launch_built_in(t_lst_d *tmp, t_data *all)
{
	t_token	*token_data;
	(void)all;
	
	token_data = (t_token *)tmp->content;
	printf("in builtins %s\n", token_data->cmd[0]);
}

void	launch_minishell(t_data *all, int num_of_tokens)
{
	t_lst_d	*tmp;
	
	if (num_of_tokens == 0)
		return ;
	tmp = all->tokens;
	if (pipe(all->pipefd))
		error_exit(all);
	while (tmp)
	{
		if (((t_token *)tmp->content)->is_built_in)
			launch_built_in(tmp, all);
		else
			launch_cmd(tmp, all);
		tmp = tmp->next;
	}
}