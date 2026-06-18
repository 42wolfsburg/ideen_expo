/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:03:31 by alappas           #+#    #+#             */
/*   Updated: 2023/09/27 01:53:18 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	two_digits(t_stack **stack_a)

{
	int	first;
	int	second;

	first = (*stack_a)->data;
	second = (*stack_a)->next->data;
	if (first > second)
		sa(stack_a);
}

void	three_digits(t_stack **stack_a)

{
	int	first;
	int	second;
	int	third;

	if (!(*stack_a)->next->next)
		return ;
	first = (*stack_a)->data;
	second = (*stack_a)->next->data;
	third = (*stack_a)->next->next->data;
	if (first < third && third < second)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (first > third && first < second)
		rra(stack_a);
	else if (second < third && third < first)
		ra(stack_a);
	else if (first > second && first < third)
		sa(stack_a);
	else if (first > second && second > third)
	{
		sa(stack_a);
		rra(stack_a);
	}
}

void	four_digits(t_stack **stack_a, t_stack **stack_b)

{
	pb(stack_a, stack_b);
	three_digits(stack_a);
	if ((*stack_b)->index == 1)
		pa(stack_a, stack_b);
	else if ((*stack_b)->index == 2)
	{
		ra(stack_a);
		pa(stack_a, stack_b);
		rra(stack_a);
	}
	else if ((*stack_b)->index == 3)
	{
		rra(stack_a);
		pa(stack_a, stack_b);
		ra(stack_a);
		ra(stack_a);
	}
	else if ((*stack_b)->index == 4)
	{
		pa(stack_a, stack_b);
		ra(stack_a);
	}
}

void	five_digits(t_stack **stack_a, t_stack **stack_b)
{
	int		pivot;

	pivot = ft_lilast(*stack_a)->position;
	stack_index(stack_a, pivot + 1);
	pivot = pivot / 2 + 1;
	while (ft_lilast((*stack_a))->position != pivot)
	{
		if ((*stack_a)->index < pivot)
		{
			pb(stack_a, stack_b);
			semi_sort(stack_a, stack_b);
		}
		else
			ra(stack_a);
	}
	while ((*stack_b))
	{
		two_digits(stack_a);
		two_digits_b(stack_b);
		pa(stack_a, stack_b);
	}
}
