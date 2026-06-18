/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:45:47 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/26 17:50:55 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sort2(t_lists **lst)
{
	sa(lst);
}

void	sort3(t_lists **lst)
{
	int	first;
	int	second;
	int	third;

	if (!(*lst)->next->next)
		return ;
	first = (*lst)->content;
	second = (*lst)->next->content;
	third = (*lst)->next->next->content;
	if (first < third && third < second)
	{
		sa(lst);
		ra(lst);
	}
	else if (first > third && first < second)
		rra(lst);
	else if (second < third && third < first)
		ra(lst);
	else if (first > second && first < third)
		sa(lst);
	else if (first > second && second > third)
	{
		sa(lst);
		rra(lst);
	}
}

void	sort4(t_lists **lst_a, t_lists **lst_b)
{
	move_distance(lst_a);
	pb(lst_b, lst_a);
	sort3(lst_a);
	pa(lst_a, lst_b);
}

void	sort5(t_lists **lst_a, t_lists **lst_b)
{
	move_distance(lst_a);
	pb(lst_b, lst_a);
	move_distance(lst_a);
	pb(lst_b, lst_a);
	sort3(lst_a);
	pa(lst_a, lst_b);
	pa(lst_a, lst_b);
}
