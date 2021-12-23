/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:45:15 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/23 21:21:35 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*PARSER:
TOKEN RECOGNITION - READ USING SHELL GRAMMAR


TOKEN RECOGNITION:

"The token shall be from the current position in the input until a token 
is delimited according to one of the rules below; the characters forming 
the token are exactly those in the input, including any quoting characters. 
If it is indicated that a token is delimited, and no characters have been 
included in a token, processing shall continue until an actual token is delimited."

!!During token recognition no substitutions shall be actually performed!!


1. end of input - current token delimeted;
2. If the current character is backslash, single-quote, or double-quote ( '\', '", or ' )'
and it is not quoted, it shall affect quoting for subsequent characters up to 
the end of the quoted text. The rules for quoting are as described in Quoting.
3. The token shall not be delimited by the end of the quoted field.

; - isn't interpreted as a delimeter, appends to the previous command or word


PARSING AT THE TOKEN LEVEL

[command name][redirection in or out of file]

if "<" or ">" next word is a name of a file 
if next sym == current - append mode in redirect output
						reading from shell in input as if it was in double quoted
open file and save in fd_in/fd_out of current token [open() flags depend on number of >>]
(if it can't be opened -> error exit with name of file as an identificator)
if "|" tokens should be placed in a linked list and pipex will be used

else ->we save all next words in char **cmd -> command name with arguments and so on
right there access/stat is performed on the first word of the token 
to check if binary file exists
or
if == builtin -> just save it as a token and move on with parsing

*/

#include "./includes/parser.h"


/*new_token() -> allocate new token and link it with a current one*/
/*manage_redirections -> new fds in current token structure*/
/*manage pipes -> if t_list *tokens->next means there is a pipe
		while tokens != NULL
			if next
				pipe()
			if (!built_in)
				fork()
			else
				built_in_management
			tokens = tokens->next*/


	/*		
			it's from the next step
	
		while (all->line[i] && all->line[i] == ' ')
			i++;
		if (!all->line[i])
			break ;
		if (all->line[i] == '>' || all->line[i] == '<')
			manage_redirections();
		else if (all->line[i] == '|')
		*/

char	*ft_strrealloc(char *old, size_t new_size)
{
	char	*new;

	new = (char *)ft_calloc(new_size, sizeof(char));
	if (!new)
	{
		free(old);
		return (NULL);
	}
	ft_strlcpy(new, old, new_size);
	free(old);
	return (new);
}

t_lst_d	*new_token(void)
{
	t_token		*new_token;
	t_lst_d		*new_lst;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->fd_out = 1;
	new_lst = ft_lstdouble_new(new_token);
	if (!new_lst)
	{
		free(new_token);
		return (NULL);
	}
	return (new_lst);
}

int		write_in_token(t_token *token, int c)
{
	size_t	i;

	if (!token->token)
	{
		token->token = (char *)ft_calloc(256, sizeof(char));
		if (!token)
			return (-1);
		token->size_of_token_line = 256;
	}
	i = 0;
	while (token->token[i] && i < token->size_of_token_line)
		i++;
	if (i == token->size_of_token_line)
	{
		token->size_of_token_line *= 2;
		token->token = ft_strrealloc(token->token, token->size_of_token_line);
		if (!token->token)
			return (-1);
	}
	token->token[i] = c;
	return (0);
}

void	manage_quotes(int c, int *quoted_flag)
{
	if (c == '\'' && !(*quoted_flag))
		*quoted_flag = SINGLE_QUOTE;
	else if (c == '"' && !(*quoted_flag))
		*quoted_flag = DOUBLE_QUOTE;
	else if ((c == '\'' && *quoted_flag == SINGLE_QUOTE) || \
									(c == '"' && *quoted_flag == DOUBLE_QUOTE))
		*quoted_flag = 0;
}

void	new_pipe_token(t_data *all)
{
	t_lst_d		*new;

	new = new_token();
	if (!new)
		error_exit(all);
	ft_lstdouble_add_back(&(all->tokens), new);
}

void	recognise_tokens(t_data *all)
{
	int			quoted_flag;
	int			i;
	t_lst_d		*tmp;

	i = -1;
	quoted_flag = 0;
	tmp = all->tokens;
	while (all->line[++i])
	{
		if (errno)
			error_exit(all);
		if (all->line[i] != '|' || quoted_flag)
			write_in_token((t_token *)tmp->content, all->line[i]);
		else
		{
			new_pipe_token(all);
			tmp = tmp->next;
		}
		manage_quotes(all->line[i], &quoted_flag);
	}
	if (quoted_flag)
	{
		all->error_message = ft_strdup("not matching quotes");
		error_exit(all);
	}
}

void	ft_put_tokens(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	printf("token = %s\n", (token->token));
	printf("size_of_token_line = %ld\n", token->size_of_token_line);
}

void	parser(t_data *all)
{
	t_lst_d	*tmp;

	tmp = all->tokens;
	recognise_tokens(all);
	while (tmp)
	{
		ft_put_tokens(tmp->content);
		tmp = tmp->next;
	}
	free_all(all);
	exit(0);
}

int		main(int argc, char **argv, char **env)
{
	t_data	*all;

	if (argc == 2)
	{
		init_data(&all, argv[1], env);
		parser(all);
	}
	else
		printf("give it only one argument please\n");
	return (0);
}
