/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charmtrx_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:14:13 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/23 19:16:41 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_charmtrx_dup(char **src)
{
	char	**new;
	int		i;

	new = (char **)ft_calloc(ft_charmtrx_len(src), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
		{
			ft_free_charmtrx(new);
			return (NULL);
		}
		i++;
	}
    return (new);
}
