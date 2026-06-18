/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:51 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 15:44:27 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sort_four(t_stack_node **a, t_stack_node **b)
{
	int	distance_from_top;
	int	distance_from_bottom;

	distance_from_top = distance(a, find_min_i);
	distance_from_bottom = stack_size(a) - distance_from_top;
	if (distance_from_top <= distance_from_bottom)
		while (distance_from_top-- != 0)
			ra(a);
	else
		while (distance_from_bottom-- != 0)
			rra(a);
	pb(a, b);
	sort_three(a, b);
	pa(a, b);
}
