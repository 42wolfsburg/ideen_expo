/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_moves_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:23:51 by alappas           #+#    #+#             */
/*   Updated: 2023/09/27 01:48:51 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	two_digits_b(t_stack **stack_b)

{
	int	first;
	int	second;

	if (!*stack_b)
		return ;
	if (!(*stack_b)->next)
		return ;
	first = (*stack_b)->data;
	second = (*stack_b)->next->data;
	if (first < second)
		sb(stack_b);
}

void	semi_sort(t_stack **stack_a, t_stack **stack_b)

{
	if (*stack_b && (*stack_b)->next && !(*stack_b)->next->next)
	{
		if ((*stack_b)->data < (*stack_b)->next->data)
			sb(stack_b);
	}
	if (!(*stack_a)->next && (*stack_a)->data > (*stack_a)->next->data)
		sa(stack_a);
	if (*stack_a && (*stack_a)->next && !(*stack_a)->next->next->next)
		three_digits(stack_a);
}
