/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_open_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 21:55:21 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/28 02:27:36 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

int	get_open_flags(int type_of_redirect)
{
	int		flags;

	if (type_of_redirect == SIMPLE_OUT || type_of_redirect == DOUBLE_OUT)
	{
		flags = O_WRONLY | O_CREAT;
		if (type_of_redirect == DOUBLE_OUT)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
	}
	else
		flags = O_RDONLY;
	return (flags);
}

static int	check_and_open(t_file *file, int *fd)
{
	file->open_flags = get_open_flags(file->type_of_redirect);
	if (file->ambiguous_redir)
		return (-1);
	if (*fd > 0)
		close(*fd);
	if (file->type_of_redirect == SIMPLE_OUT || file->type_of_redirect == DOUBLE_OUT)
		*fd = open(file->file_name, file->open_flags, 00644);
	else if (file->type_of_redirect == SIMPLE_IN)
		*fd = open(file->file_name, file->open_flags);
	else
		*fd = file->heredoc_pipe[0];
	if (*fd == -1)
		return (-1);
	return (1);
}

int	open_all_files(t_token *token, t_data *all)
{
	t_list	*tmp;
	int		res;

	tmp = token->files;
	while (tmp)
	{
		if (((t_file *)tmp->content)->type_of_redirect == SIMPLE_OUT || \
		((t_file *)tmp->content)->type_of_redirect == DOUBLE_OUT)
			res = check_and_open((t_file *)tmp->content, &(token->fd_out));
		else
			res = check_and_open((t_file *)tmp->content, &(token->fd_in));
		if (res < 0)
		{
			all->error_ident = ft_strdup(((t_file *)tmp->content)->file_name);
			if (((t_file *)tmp->content)->ambiguous_redir)
				all->error_message = ft_strdup("ambiguous redirect");
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}