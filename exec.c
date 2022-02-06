/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 01:12:03 by dselmy            #+#    #+#             */
/*   Updated: 2022/02/05 17:18:33 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"
#include "./buildins/buildins.h"

int	find_path(char **paths_tmp, char **cmd_args, char **new_path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (paths_tmp[++i])
	{
		tmp = ft_strjoin(paths_tmp[i], "/");
		if (!tmp)
			return (-1);
		*new_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!*new_path)
			return (-1);
		if (access(*new_path, F_OK & X_OK) == 0)
			return (1);
		free(*new_path);
	}
	*new_path = NULL;
	return (0);
}

int	find_exec(char **cmd_args, char **env)
{
	int		i;
	char	**paths_tmp;
	char	*exec_path;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
	paths_tmp = ft_split(env[i] + 5, ':');
	if (!paths_tmp || find_path(paths_tmp, cmd_args, &exec_path) < 0)
	{
		ft_free_charmtrx(paths_tmp);
		return (-1);
	}
	ft_free_charmtrx(paths_tmp);
	if (exec_path)
		execve(exec_path, cmd_args, env);
	return (0);
}

void	check_directory(char *bin_name, t_data *all)
{
	struct stat	data;

	if (!stat(bin_name, &data))
	{
		if (data.st_mode & S_IFDIR)
		{
			all->error_message = ft_strdup("is a directory");
			all->error_exit_code = 126;
		}
	}
}

int	exec_builtin(t_token *token, t_data *all)
{
	if (!ft_strncmp(token->cmd[0], "pwd", 4))
		all->last_exit_status = ft_pwd(token->fd_out, all);
	else if (!ft_strncmp(token->cmd[0], "cd", 3))
		all->last_exit_status = ft_cd(token->cmd + 1, &(all->env));
	else if (!ft_strncmp(token->cmd[0], "echo", 5))
		all->last_exit_status = ft_echo(token->fd_out, token->cmd + 1);
	else if (!ft_strncmp(token->cmd[0], "exit", 5))
		all->last_exit_status = ft_exit(token->cmd + 1, &all);
	else if (!ft_strncmp(token->cmd[0], "env", 4))
		all->last_exit_status = ft_env(token->fd_out, all->env);
	else if (!ft_strncmp(token->cmd[0], "unset", 6))
		all->last_exit_status = ft_unset(token->cmd + 1, &all);
	else if (!ft_strncmp(token->cmd[0], "export", 7))
		all->last_exit_status = ft_export(token->fd_out, token->cmd + 1, &all);
	return (all->last_exit_status);
}

void	exec_cmd(char **cmd_args, t_data *all)
{
	if (!cmd_args[0])
		return ;
	if (cmd_args[0][0] != '/' && cmd_args[0][0] != '.')
	{
		if (find_exec(cmd_args, all->env) < 0)
		{
			all->error_exit_code = 1;
			return ;
		}
		all->error_message = ft_strdup("command not found");
	}
	else
	{
		if (access(cmd_args[0], F_OK & X_OK) == 0)
		{
			check_directory(cmd_args[0], all);
			execve(cmd_args[0], cmd_args, all->env);
		}
	}
	all->error_exit_code = 127;
	all->error_ident = ft_strdup(cmd_args[0]);
}
