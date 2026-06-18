/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:47:04 by alappas           #+#    #+#             */
/*   Updated: 2024/04/14 01:06:31 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	main_sort(t_stack **stack_a, t_stack **stack_b)

{
	t_stack	*mid;

	sort_a(stack_a, stack_b);
	while (sort_check_a(*stack_a) != 0 || (*stack_b) != NULL)
	{
		final_sort(stack_a, stack_b);
		if (!*stack_b)
			break ;
	}
	mid = (*stack_a);
	while ((*stack_a)->data <= mid->data)
		mid = mid->next;
	stack_sign(stack_a);
	while (sort_check_a(*stack_a) != 0)
	{
		if (mid->sign == '-')
			rra(stack_a);
		else
			ra(stack_a);
	}
	return (0);
}

int	sort_a(t_stack **stack_a, t_stack **stack_b)

{
	int		pivot;

	pivot = ft_lilast(*stack_a)->position;
	stack_index(stack_a, pivot + 1);
	if (pivot <= 3)
	{
		three_digits(stack_a);
		return (1);
	}
	pivot = pivot / 2 + 1;
	while (ft_lilast((*stack_a))->position != pivot)
	{
		if ((*stack_a)->index <= pivot)
			pb(stack_a, stack_b);
		else
			ra(stack_a);
	}
	return (sort_a(stack_a, stack_b));
}

void	stack_final_cost(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*head_a;
	t_stack	*head_b;
	t_stack	*target_node;
	long	target_node_data;

	head_a = (*stack_a);
	head_b = (*stack_b);
	while (*stack_b)
	{
		target_node_data = LONG_MAX;
		while ((*stack_a))
		{
			if ((*stack_a)->data > (*stack_b)->data
				&& (*stack_a)->data < target_node_data)
			{
				target_node_data = (*stack_a)->data;
				target_node = (*stack_a);
				(*stack_a) = (*stack_a)->next;
			}
			else
				(*stack_a) = (*stack_a)->next;
		}
		stack_final_cost_helper(stack_a, stack_b, &target_node, head_a);
	}
	(*stack_b) = head_b;
}

void	final_sort(t_stack **stack_a, t_stack **stack_b)

{
	t_stack	*target_node;
	t_stack	*head_b;

	stack_cost_a(stack_a);
	stack_cost_b(stack_b);
	stack_final_cost(stack_a, stack_b);
	head_b = (*stack_b);
	target_node = (*stack_b);
	while (*stack_b)
	{
		if ((*stack_b)->final_cost < target_node->final_cost)
			target_node = (*stack_b);
		else if ((*stack_b)->final_cost == target_node->final_cost)
		{
			if ((*stack_b)->data < target_node->data)
				target_node = (*stack_b);
		}
		(*stack_b) = (*stack_b)->next;
	}
	(*stack_b) = head_b;
	inside_push(stack_a, stack_b, target_node);
}

void	inside_push(t_stack **stack_a, t_stack **stack_b, t_stack *target_node)

{
	t_stack	*head_a;
	t_stack	*inner_node;

	head_a = (*stack_a);
	while (target_node->target_pos != (*stack_a)->position)
		(*stack_a) = (*stack_a)->next;
	inner_node = (*stack_a);
	(*stack_a) = head_a;
	double_rotate(inner_node, target_node, stack_a, stack_b);
	inside_push_helper(stack_a, stack_b, target_node, inner_node);
	pa(stack_a, stack_b);
}
