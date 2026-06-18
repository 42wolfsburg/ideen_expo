/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:16:03 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 18:07:32 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	max_amount_bits;
	int	bit;
	int	size;
	int	i;

	max_amount_bits = get_max_amount_bits(*stack_a);
	bit = 0;
	while (bit < max_amount_bits)
	{
		size = ft_lstsize(*stack_a);
		i = 0;
		while (i < size)
		{
			if ((((*stack_a)->index >> bit) & 1) == 1)
				ra (stack_a);
			else
				pb (stack_a, stack_b);
			i++;
		}
		while (*stack_b)
			pa (stack_a, stack_b);
		bit++;
	}
}
