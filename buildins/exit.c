#include "buildins.h"
#include "../includes/parser.h"

long long int	ft_atol(const char *str)
{
	int				i;
	int				neg;
	long long int	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			neg = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	nbr *= neg;
	return (nbr);
}

static int	error_too_many_args(int mode)
{
	if (mode != 1)
		write(2, "exit\n", 5);
	write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}

static int	error_numeric_argument(char *wrong_argument, char **args, \
	t_data **all, int mode)
{
	if (mode != 1)
		write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, wrong_argument, ft_strlen(wrong_argument));
	write(2, ": numeric argument required\n", 28);
	ft_free_charmtrx(args);
	free_all(all);
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
	num_len = 1;
	if ((argument[0] == '+' && code < 0) || (argument[0] != '-' && code < 0))
		return (1);
	if (argument[0] == '+')
		str_len--;
	if (code < 0)
	{
		code *= -1;
		str_len--;
	}
	while ((code /= 10) > 0)
		num_len++;
	if (str_len != num_len)
		return (1);
	return (0);
}

static long int	norm_exit(long int code, char **args, t_data **all, int mode)
{
	if (args[1] && check_overflow(code, args[1]))
		return (error_numeric_argument(args[1], args, all, mode));
	if (mode != 1)
	{
		write(2, "exit\n", 5);
	}
	free_all(all);
	ft_free_charmtrx(args);
	return (code);
}

int	ft_exit(char **args, t_data **all, int mode)
{
	int			index;

	index = -1;
	errno = 0;
	if (args[1])
	{
		if (!args[2])
		{
			while (args[1][++index])
				if (!ft_isdigit(args[1][index]) && !(index == 0 && \
					(args[1][index] == '-' || args[1][index] == '+')))
					break ;
			if (args[1][index] == '\0')
				exit(norm_exit(ft_atol(args[1]), args, all, mode));
			else
				exit(error_numeric_argument(args[1], args, all, mode));
		}
		else
			return (error_too_many_args(mode));
	}
	exit(norm_exit(0, args, all, mode));
}
