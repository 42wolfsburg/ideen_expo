/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:33:17 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 13:37:19 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	big_sort(t_stack_node **a, t_stack_node **b, int argc)
{
	int	num;
	int	pushcount;

	num = chunk_size(argc);
	pushcount = 0;
	while (*a)
	{
		if ((*a)->index <= pushcount)
		{
			pb(a, b);
			pushcount++;
			if (stack_size(b) > 1)
				rb(b);
		}
		else if ((*a)->index <= pushcount + num)
		{
			pb(a, b);
			pushcount++;
		}
		else
			ra(a);
	}
}

void	sort(t_stack_node **a, t_stack_node **b, int argc)
{
	if (argc == 2)
		sort_two(a);
	else if (argc == 3)
		sort_three(a, b);
	else if (argc == 4)
		sort_four(a, b);
	else if (argc == 5)
		sort_five(a, b);
	else
		big_sort(a, b, argc);
}

int	chunk_size(int ac)
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
