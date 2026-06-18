/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:55:07 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/29 01:36:29 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	distance(t_lists **lst, int (*f)(t_lists **lst))
{
	int		distance;
	t_lists	*tmp;

	distance = 0;
	tmp = *lst;
	while ((*lst) && f(&tmp) != (*lst)->content)
	{
		*lst = (*lst)->next;
		distance++;
	}
	*lst = tmp;
	return (distance);
}

void	move_distance(t_lists **lst_a)
{
	int		to_up;
	int		to_down;

	to_up = 0;
	to_down = ft_lst_size(lst_a);
	to_up += distance(lst_a, find_min);
	to_down -= distance(lst_a, find_min);
	if (to_up <= to_down)
	{
		while (to_up > 0)
		{
			ra(lst_a);
			to_up--;
		}
	}
	else
	{
		while (to_down > 0)
		{
			rra(lst_a);
			to_down--;
		}
	}
}

void	find_index(t_lists **lst)
{
	int		index;
	t_lists	*head;

	head = *lst;
	index = 0;
	while (*lst)
	{
		if ((*lst)->content == find_min(lst))
		{
			(*lst)->index = index;
			index++;
			*lst = head;
			continue ;
		}
		*lst = (*lst)->next;
	}
	*lst = head;
}
