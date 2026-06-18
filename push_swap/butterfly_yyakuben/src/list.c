/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:56:06 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/28 22:21:54 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstadd_back(t_lists **lst, t_lists *new)
{
	t_lists	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

void	lst_add_front(t_lists **lst, t_lists *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_lists	*ft_lstnew(int content)
{
	t_lists	*lst;

	lst = malloc(sizeof(t_lists));
	(lst)->content = content;
	(lst)->index = -1;
	(lst)->next = NULL;
	return (lst);
}

t_lists	*ft_lstlast(t_lists *lst)
{
	t_lists	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_listclear(t_lists **lst)
{
	t_lists	*head;

	while (*lst)
	{
		head = (*lst)->next;
		free(*lst);
		(*lst) = head;
	}
}
