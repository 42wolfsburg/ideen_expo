/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:03:06 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 18:07:25 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if (!stack_a || !(*stack_a)->next || !(*stack_a)->next->next)
		return ;
	while (!is_sorted((*stack_a)))
	{
		first = (*stack_a);
		second = first-> next;
		third = second-> next;
		if (first-> value > second-> value && first-> value < third-> value)
			sa(&(*stack_a));
		else if (first-> value > second-> value
			&& first-> value > third-> value)
			ra(&(*stack_a));
		else if (first-> value < second-> value
			&& second-> value > third-> value)
			rra(&(*stack_a));
	}
}
