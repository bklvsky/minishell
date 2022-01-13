/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:03:45 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/13 22:40:03 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	redirect_fds(t_lst_d *token, t_data *all)
{
	t_token	*token_data;

	token_data = (t_token *)token->content;
	if (open_all_files(token_data, all) < 0)
		error_launch_exit(token, all);
	printf("fd in = %d, fd out = %d\n", token_data->fd_in, token_data->fd_out);
	if (token_data->fd_in)
	{
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
		waitpid(pid, NULL, 0);
	}
}

void	launch_minishell(t_data *all, int num_of_tokens)
{
	t_lst_d	*tmp;
	
	printf("num of tokens = %d\n", num_of_tokens);
	if (num_of_tokens == 0)
		return ;
	tmp = all->tokens;
	while (tmp)
	{
		launch_cmd(tmp, all);
		tmp = tmp->next;
	}
}