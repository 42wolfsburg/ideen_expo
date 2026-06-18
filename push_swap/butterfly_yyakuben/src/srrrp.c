/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srrrp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 19:21:01 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/28 21:17:10 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	lst_swap(t_lists **lst)
{
	t_lists	*head;
	t_lists	*tmp;

	if (*lst == NULL || (*lst)->next == NULL)
		return (0);
	head = (*lst)->next;
	tmp = (*lst)->next->next;
	head->next = *lst;
	(*lst)->next = tmp;
	*lst = head;
	return (1);
}

int	lst_rotate(t_lists **lst)
{
	t_lists	*tmp;
	t_lists	*head;

	if (!lst)
		return (0);
	tmp = *lst;
	head = (*lst)->next;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = tmp;
	(*lst)->next->next = NULL;
	*lst = head;
	return (1);
}

int	lst_reverse_rotate(t_lists **lst)
{
	t_lists	*head;
	t_lists	*last;

	if (!lst)
		return (0);
	last = *lst;
	while (last->next->next)
		last = last->next;
	head = last->next;
	last->next = NULL;
	head->next = (*lst);
	*lst = head;
	return (1);
}

int	push(t_lists **lst_a, t_lists **lst_b)
{
	t_lists	*data;

	data = (*lst_b);
	(*lst_b) = (*lst_a);
	if (*lst_a)
		(*lst_a) = (*lst_a)->next;
	(*lst_b)->next = data;
	return (1);
}
