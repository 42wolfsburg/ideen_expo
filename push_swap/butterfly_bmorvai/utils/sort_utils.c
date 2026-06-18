/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:33:26 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 18:41:36 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	distance(t_stack_node **b, int (*f)(t_stack_node **stack))
{
	int				distance;
	t_stack_node	*current;

	distance = 0;
	current = *b;
	while (current->value != f(b))
	{
		current = current->next;
		distance++;
	}
	return (distance);
}

void	go_home(t_stack_node **a, t_stack_node **b)
{
	int	distance_from_top;
	int	distance_from_bottom;

	if (!*b)
		return ;
	if (!(*b)->next)
	{
		pa(a, b);
		return ;
	}
	distance_from_top = distance(b, find_max);
	distance_from_bottom = stack_size(b) - distance_from_top;
	if (distance_from_top <= distance_from_bottom)
		while (distance_from_top-- != 0)
			rb(b);
	else
		while (distance_from_bottom-- != 0)
			rrb(b);
	pa(a, b);
}
