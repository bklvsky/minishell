/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:30:10 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/04 01:25:10 by dselmy           ###   ########.fr       */
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

char	*get_file_name(char *line, int *i, t_data *all)
{
	char	*name;
	char	*tmp;
	char	*tmp2;
	int		len;
	int		start;
	int		quoted_flag;

	len = 0;
	quoted_flag = 0;
	name = NULL;
	start = *i;
	while (line[start + len])
	{
		if ((line[start + len] == ' ' || is_redirect(line[start + len])) && !quoted_flag)
			break ;
		if (line[start + len] == '$' && quoted_flag != SINGLE_QUOTE)
		{
			start = start + len + expand_env_var(&name, line + start + len, all) + 1;
			len = 0;
		}
		else if (!manage_quotes(line[start + len], &quoted_flag))
			len += 1;
		else
		{
			tmp = name;
			tmp2 = ft_substr(line, start, len);
			name = ft_strjoin(tmp, tmp2);
			free(tmp);
			if (!tmp2)
			{
				free(name);
				error_exit(all);
			}
			free(tmp2);
			if (!name)
				error_exit(all);
			start = start + len + 1;
			len = 0;
		}
	}
	tmp = name;
	tmp2 = ft_substr(line, start, len);
	name = ft_strjoin(tmp, tmp2);
	free(tmp);
	if (!tmp2)
	{
		free(name);
		error_exit(all);
	}
	free(tmp2);
	if (!name)
		error_exit(all); 
	*i += start + len;
	return (name);
}

int	check_access_rigths(t_file *file)
{
	int		access_mode;
	
	if (file->type_of_redirect == SIMPLE_OUT || file->type_of_redirect == DOUBLE_OUT)
		access_mode = 2;
	else
		access_mode = 3;
	return (access(file->file_name, access_mode));
}

void	manage_redirections(int *i, t_token *cur_token, t_data *all)
{
	t_file	*new_file;
	t_list	*new_lst;
//	int		open_flags;

	new_file = (t_file *)malloc(sizeof(t_file));
	new_lst = ft_lstnew(new_file);
	if (!new_file || !new_lst)
		error_exit(all);
	ft_lstadd_back(&(cur_token->files), new_lst);
	new_file->type_of_redirect = get_type_of_redirect(cur_token->token, i);
	skip_whitespaces(i, cur_token->token);
	new_file->file_name = get_file_name(cur_token->token, i, all);
	if (!new_file->file_name || !new_file->file_name[0])
	{
		all->error_message = ft_strdup("syntax error near unexpected token");
	//	free(new_file->file_name);
		error_exit(all);
	}
	if (check_access_rigths(new_file) < 0)
	{
		all->error_ident = ft_strdup(new_file->file_name);
		error_exit(all);
	}
}

/*	if (new_file->type_of_redirect == SIMPLE_OUT || type_of_redirect == DOUBLE_OUT)
		cur_token->fd_out = open(file_name, open_flags, 00644);
	else
		cur_token->fd_in = open(file_name, open_flags);
	if (errno)
	{
		all->error_ident = file_name;
		error_exit(all);
	}*/
//	printf("file name = %s\n", file_name);