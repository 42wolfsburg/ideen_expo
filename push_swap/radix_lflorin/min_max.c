/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorin <lflorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:02:29 by lea               #+#    #+#             */
/*   Updated: 2026/05/29 11:24:02 by lflorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*get_min(t_stack *stack_a)
{
	t_stack	*min;
	t_stack	*temp;

	if (! stack_a)
		return (NULL);
	min = stack_a;
	temp = stack_a;
	while (temp)
	{
		if (temp -> value < min -> value)
			min = temp;
		temp = temp -> next;
	}
	return (min);
}

t_stack	*get_max(t_stack *stack_a)
{
	t_stack	*max;
	t_stack	*temp;

	if (!stack_a)
		return (NULL);
	max = stack_a;
	temp = stack_a;
	while (temp)
	{
		if (temp -> value > max -> value)
			max = temp;
		temp = temp -> next;
	}
	return (max);
}
