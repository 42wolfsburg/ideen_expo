/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:02:51 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 18:07:17 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_5(t_stack **stack_a, t_stack **stack_b)
{
	int	i;

	i = ft_lstsize((*stack_a));
	while (i > 3)
	{
		sort_5_helper (stack_a);
		pb (&(*stack_a), &(*stack_b));
		i--;
	}
	if (i == 3 && !is_sorted(*stack_a))
		sort_3 (stack_a);
	while (*stack_b != NULL)
		pa (&(*stack_a), &(*stack_b));
}

void	sort_5_helper(t_stack **stack_a)
{
	t_stack	*min;

	min = get_min(*stack_a);
	if (min == (*stack_a))
		return ;
	while (min != (*stack_a))
	{
		if (min == (*stack_a)-> next || min == (*stack_a)-> next-> next)
		{
			ra (&(*stack_a));
		}
		else
		{
			rra(&(*stack_a));
		}
	}
}
