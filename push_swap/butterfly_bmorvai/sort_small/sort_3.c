/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:47 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/18 09:18:33 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sort_three_low(t_stack_node **a, t_stack_node **b, int second,
		int third)
{
	if (second < third)
		return ;
	else if (second > third)
	{
		pb(a, b);
		ra(a);
		pa(a, b);
	}
}

void	sort_three_mid(t_stack_node **a, int first,
		int second)
{
	if (first > second)
	{
		sa(a);
	}
	else if (first < second)
		rra(a);
}

void	sort_three_high(t_stack_node **a, t_stack_node **b, int first,
		int second)
{
	if (first > second)
	{
		pb(a, b);
		ra(a);
		pa(a, b);
		ra(a);
	}
	else if (first < second)
		ra(a);
}

void	sort_three(t_stack_node **a, t_stack_node **b)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->index;
	second = (*a)->next->index;
	third = (*a)->next->next->index;
	if (first < second && first < third)
		sort_three_low(a, b, second, third);
	else if (first > second && first > third)
		sort_three_high(a, b, first, second);
	else
		sort_three_mid(a, first, second);
}
