/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_delete_later.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:34:46 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/13 22:36:36 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/parser.h"

void	ft_put_tokens(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	printf("token = %s\n", (token->token));
	printf("size_of_token_line = %ld\n", token->size_of_token_line);
}

void	put_files(void *content)
{
	t_file *file;

	if (!content)
	{
		printf("no file for you\n");
		return ;
	}
	file = (t_file *)content;
	printf("file_name = %s\n", file->file_name);
	printf("type of redirect = %d\n", file->type_of_redirect);
}

void	ft_put_read_token(void *content)
{
	t_token	*token;
	int		i = -1;

	printf("in put read token\n");
	token = (t_token *)content;
	if (token->cmd)
	{
		while (token->cmd[++i])
			printf("arg%d = %s\n", i, token->cmd[i]);
	}
	ft_lstiter(token->files, &put_files);
}
