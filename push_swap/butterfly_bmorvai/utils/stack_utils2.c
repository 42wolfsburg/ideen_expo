/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:33:32 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 14:56:28 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	find_min(t_stack_node **a)
{
	t_stack_node	*current;
	int				min;

	current = *a;
	min = INT_MAX;
	while (current)
	{
		if (current->index == -1)
		{
			if (current->value < min)
				min = current->value;
		}
		current = current->next;
	}
	return (min);
}

int	find_min_i(t_stack_node **a)
{
	t_stack_node	*current;
	int				min;

	current = *a;
	min = INT_MAX;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	find_max(t_stack_node **b)
{
	t_stack_node	*current;
	int				max_index;
	long			max_value;

	current = *b;
	max_index = 0;
	while (current)
	{
		if (current->index > max_index)
		{
			max_index = current->index;
			max_value = current->value;
		}
		current = current->next;
	}
	return (max_value);
}

void	find_index(t_stack_node **stack)
{
	t_stack_node	*current;
	int				min;
	int				index;

	index = 0;
	current = *stack;
	while (find_min(stack) != INT_MAX)
	{
		current = *stack;
		min = find_min(stack);
		while (current)
		{
			if (current->value == min && current->index == -1)
				current->index = index++;
			current = current->next;
		}
	}
}
