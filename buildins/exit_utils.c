/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 20:21:21 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/21 20:21:22 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "buildins.h"

long int	check_overflow_sub(long int a, int *str_len)
{
	if (a < 0)
	{
		a *= -1;
		*str_len = *str_len - 1;
	}
	return (a);
}

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
