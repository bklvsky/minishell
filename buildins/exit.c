/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:21:07 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/21 20:21:11 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "../includes/parser.h"

static int	error_too_many_args(void)
{
	write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}

static int	error_numeric_argument(char *wrong_argument, t_data **all)
{
	write(2, "minishell: exit: ", 17);
	write(2, wrong_argument, ft_strlen(wrong_argument));
	write(2, ": numeric argument required\n", 28);
	free_all(*all);
	return (2);
}

static int	check_overflow(long int code, char *argument)
{
	int			str_len;
	int			num_len;

	if (!ft_strncmp(argument, "9223372036854775808", ft_strlen(argument)))
		return (1);
	if (!ft_strncmp(argument, "-9223372036854775808", ft_strlen(argument)))
		return (0);
	str_len = ft_strlen(argument);
	num_len = 0;
	if ((argument[0] == '+' && code < 0) || (argument[0] != '-' && code < 0))
		return (1);
	if (argument[0] == '+')
		str_len--;
	code = check_overflow_sub(code, &str_len);
	while (code > 0)
	{
		code /= 10;
		num_len++;
	}
	if (str_len != num_len)
		return (1);

	return (0);
}

static long int	norm_exit(long int code, char **args, t_data **all)
{
	if (args[0] && check_overflow(code, args[0]))
		return (error_numeric_argument(args[0], all));
	write(2, "exit\n", 6);
	free_all(*all);
	return (code);
}

int	ft_exit(char **args, t_data **all)
{
	int			index;

	index = -1;
	errno = 0;
	if (args[0])
	{
		if (!args[1])
		{
			while (args[0][++index])
				if (!ft_isdigit(args[0][index]) && !(index == 0 && \
                   (args[0][index] == '-' || args[0][index] == '+')))
					break;
			if (args[0][index] == '\0')
				exit(norm_exit(ft_atol(args[0]), args, all));
			else
				exit(error_numeric_argument(args[0], all));
		} else
			return (error_too_many_args());
	}
	exit(norm_exit(0, args, all));
}
