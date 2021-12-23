/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:50:39 by dselmy            #+#    #+#             */
/*   Updated: 2021/12/23 20:35:58 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	ft_lstdouble_add_front(t_lst_d **head, t_lst_d *new)
{
	if (head)
	{
		if (new)
		{
			if (*head)
				(*head)->prev = new;
			new->next = *head;
			new->prev = NULL;
			*head = new;
		}
	}
}

void	ft_lstdouble_add_back(t_lst_d **head, t_lst_d *new)
{
	t_lst_d	*tmp;

	if (head)
	{
		tmp = *head;
		if (tmp)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = NULL;
		}
		else
			*head = new;
	}
}

t_lst_d	*ft_lstdouble_new(void *elem)
{
	t_lst_d	*new;

	new = (t_lst_d *)malloc(sizeof(t_lst_d));
	if (!new)
		return (NULL);
	if (elem)
		new->content = elem;
	else
		new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lst_d	*ft_lstdouble_last(t_lst_d *lst)
{
	t_lst_d	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lstdouble_delone(t_lst_d *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

void	ft_lstdouble_clear(t_lst_d **lst, void (*del)(void *))
{
	t_lst_d	*tmp;

	if (lst && del && *lst)
	{
		while ((*lst)->next)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lstdouble_delone(tmp, del);
		}
		ft_lstdouble_delone(*lst, del);
		*lst = NULL;
	}
}