/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:45:15 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/27 04:53:02 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

t_lst_d	*new_token(void)
{
	t_token		*new_token;
	t_lst_d		*new_lst;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_lst = ft_lstdouble_new(new_token);
	if (!new_lst)
	{
		free(new_token);
		return (NULL);
	}
	return (new_lst);
}

int		write_in_token(t_token *token, char c)
{
	size_t	i;

	if (!token->token)
	{
		token->token = (char *)ft_calloc(256, sizeof(char));
		if (!token)
			return (-1);
		token->size_of_token_line = 256;
	}
	i = ft_strlen(token->token);
	if (i == token->size_of_token_line - 1)
	{
		token->size_of_token_line *= 2;
		token->token = ft_strrealloc(token->token, token->size_of_token_line);
		if (!token->token)
			return (-1);
	}
	token->token[i] = c;
	return (0);
}

int	check_closed_quotes(int quoted_flag, t_data *all)
{
	if (quoted_flag)
	{
		if (quoted_flag == SINGLE_QUOTE)
			all->error_message = ft_strdup\
			("unexpected newline while looking for matching '''");
		else
			all->error_message = ft_strdup\
			("unexpected newline while looking for matching '\"'");
		return (error_syntax_exit(0, NULL, all)); // not exit but back to the cycle
	}
	return (0);
}

void	new_pipe_token(t_data *all)
{
	t_lst_d		*new;

	new = new_token();
	if (!new)
		error_exit(all);
	ft_lstdouble_add_back(&(all->tokens), new);
}

int	recognise_tokens(t_data *all)
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
		manage_quotes(all->line[i], &quoted_flag);
		if (all->line[i] != '|' || quoted_flag)
			write_in_token((t_token *)tmp->content, all->line[i]);
		else
		{
			new_pipe_token(all);
			tmp = tmp->next;
		}
	}
	return (check_closed_quotes(quoted_flag, all));
}

int	parser(t_data *all)
{
	if (recognise_tokens(all) < 0)
		return (-1);
	if (parse_token(all) < 0)
		return (-1);
	check_built_ins(all->tokens);
	return (0);
}

void	unknown_arguments(int argc, char **argv)
{
	int		i;

	i = 0;
	write(2, "minishell: unknown argument: ", 29);
	while (i < argc)
	{
		write(2, "\"", 1);
		write(2, argv[i], ft_strlen(argv[i]));
		write(2, "\", ", 3);
		i += 1;
	}
	write(2, "\nUsage: ./minishell [--no arguments]\n", 37);
}

int		main(int argc, char **argv, char **envp)
{
	t_data	*all;
	char	*inpt;

	rl_catch_signals = 0;
	if (argc == 1)
	{
		init_struct_first(&all, envp);
		while(1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &sig_int);
			inpt = readline("minishell: ");
			init_data(all, inpt);
			if (*inpt)
			{
				add_history(inpt);
				if (!parser(all))
					launch_minishell(all, ft_lstdouble_size(all->tokens));
			}
			free_cmd(all);
		}
	}
	else
		unknown_arguments(argc, argv);
	return (0);
}
