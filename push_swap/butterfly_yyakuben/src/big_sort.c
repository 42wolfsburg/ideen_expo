/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:24:54 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/28 20:19:08 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	big_sort(t_lists **lst_a, t_lists **lst_b, int ac)
{
	int		num;
	int		count;

	num = best_moment(ac);
	count = 0;
	while (*lst_a)
	{
		if ((*lst_a)->index <= count)
		{
			pb(lst_b, lst_a);
			if (ft_lst_size(lst_b) > 1)
				rb(lst_b);
			count++;
		}
		else if ((*lst_a)->index <= count + num)
		{
			pb(lst_b, lst_a);
			count++;
		}
		else
			ra(lst_a);
	}
}

void	go_home(t_lists **lst_b)
{
	int		to_up;
	int		to_down;

	to_up = 0;
	to_down = ft_lst_size(lst_b);
	to_up += distance(lst_b, find_max);
	to_down -= distance(lst_b, find_max);
	if (to_up <= to_down)
	{
		while (to_up > 0)
		{
			rb(lst_b);
			to_up--;
		}
	}
	else
	{
		while (to_down > 0)
		{
			rrb(lst_b);
			to_down--;
		}
	}
}

int	best_moment(int ac)
{
	int	num;
	int	count;

	num = 1;
	count = ac;
	if (20 > count && count > 5)
		return (num);
	else if (41 > count && count >= 20)
		num += 0;
	else if (62 > count && count >= 41)
		num += 3;
	else if (83 > count && count >= 62)
		num += 6;
	else if (127 >= count && count >= 83)
		num += 14;
	else if (235 > count && count > 127)
		num += 17;
	else if (343 > count && count >= 235)
		num += 20;
	else if (451 > count && count >= 343)
		num += 25;
	else if (451 <= count)
		num += 29;
	return (num);
}
