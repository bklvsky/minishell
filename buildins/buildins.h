/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyr <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:08:12 by sstyr             #+#    #+#             */
/*   Updated: 2022/01/16 20:08:13 by sstyr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../includes/parser.h"

typedef struct s_env
{
	char	*name;
	char	*val;
}			t_env;

int		ft_echo(char **args);
int		ft_cd(char **args, char ***env);
int		ft_pwd(void);
int		ft_exit(char **args, t_data **all, int mode);

t_list	*read_env(char **strs);
void	print_env(t_list **env_list);
t_env	*get_var_by_name(t_list **env_list, char *name);
char	*get_val_by_name(t_list **env_list, char *name);
char	*change_var_val(t_list **env_list, char *name, char *new_val);
char	**env_to_strs(t_list **env_list);
void	clear_env(t_list **env_list);
int		error_print_return(char *message);
void	check_env_free(t_list **env_list, char ***env);

#endif
