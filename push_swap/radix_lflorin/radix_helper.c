/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:49:26 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 14:27:35 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_index(int *sorted, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted[i] == value)
			return (i);
		i++;
	}
	return (-1);
}
// It scans the sorted array from left to right and returns
// the position where `value` is found, so that position 
// becomes the number’s rank.

void	assign_indexes(t_stack *stack_a)
{
	t_stack	*current_stack;
	int		*sorted;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(stack_a);
	sorted = malloc(sizeof(int) * size);
	if (!sorted)
		return ;
	current_stack = stack_a;
	while (current_stack)
	{
		sorted[i++] = current_stack->value;
		current_stack = current_stack->next;
	}
	sort_int_array (sorted, size);
	current_stack = stack_a;
	while (current_stack)
	{
		current_stack->index = find_index(sorted, size, current_stack->value);
		current_stack = current_stack->next;
	}
	free (sorted);
}

void	sort_int_array(int *array, int size)
{
	int	i;
	int	ii;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		ii = 0;
		while (ii < size - i - 1)
		{
			if (array[ii] > array[ii + 1])
			{
				temp = array[ii];
				array[ii] = array[ii + 1];
				array[ii + 1] = temp;
			}
			ii++;
		}
		i++;
	}
}

int	get_max_amount_bits(t_stack *stack_a)
{
	int	max;
	int	bits;

	max = 0;
	while (stack_a)
	{
		if (stack_a->index > max)
		{
			max = stack_a->index;
		}
		stack_a = stack_a->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}
