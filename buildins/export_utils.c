/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:41:24 by dselmy            #+#    #+#             */
/*   Updated: 2022/01/28 04:12:53 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

static void	ft_swap(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

void	sort_environ(char **env, int left, int right)
{
	char	*mid_str;
	int		l;
	int		r;

	mid_str = env[left + (right - left) / 2];
	l = left;
	r = right;
	while (l < r)
	{
		while ((ft_strncmp(env[l], mid_str, ft_strlen(env[l]))) < 0)
			l++;
		while ((ft_strncmp(env[r], mid_str, ft_strlen(env[r]))) > 0)
			r--;
		if (l <= r)
		{
			ft_swap(&env[l], &env[r]);
			r -= 1;
			l += 1;
		}
	}
	if (l < right)
		sort_environ(env, l, right);
	if (r > left)
		sort_environ(env, left, r);
}

void	export_env(int fd_out, char **env)
{
	char	*eq_ptr;

	while (*env)
	{
		eq_ptr = ft_strchr(*env, '=');
		write(fd_out, "declare -x ", 11);
		if (eq_ptr)
		{
			write(fd_out, *env, eq_ptr - *env + 1);
			eq_ptr += 1;
			write(fd_out, "\"", 2);
			write(fd_out, eq_ptr, ft_strlen(eq_ptr));
			write(fd_out, "\"", 1);
		}
		else
			write(fd_out, *env, ft_strlen(*env));
		write(fd_out, "\n", 1);
		env++;
	}
}

void	put_error_export(char *unvalid_arg)
{
	write(2, "minishell: export: ", 19);
	write(2, "'", 1);
	write(2, unvalid_arg, ft_strlen(unvalid_arg));
	write(2, "': not a valid identifier\n", 26);
}
