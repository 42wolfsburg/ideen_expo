/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 01:50:26 by alappas           #+#    #+#             */
/*   Updated: 2024/04/14 01:06:45 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	stack_index(t_stack **stack, int argc)
{
	t_stack	*head;
	t_stack	*temp;
	int		index;
	int		value;

	if (!*stack)
		return ;
	temp = NULL;
	index = 1;
	value = node_max(stack);
	head = (*stack);
	index_reset(stack);
	while (argc != 1)
	{
		index_helper(&temp, stack, value);
		temp->index = index;
		index++;
		argc--;
		(*stack) = head;
		value = node_max(stack);
	}
	temp = head;
	stack_position(stack);
}

void	index_reset(t_stack **stack)

{
	t_stack	*head;

	head = (*stack);
	while (*stack)
	{
		(*stack)->index = 0;
		(*stack) = (*stack)->next;
	}
	(*stack) = head;
}

void	index_helper(t_stack **temp, t_stack **stack, int value)

{
	while (*stack)
	{
		if (value >= (*stack)->data && (*stack)->index == 0)
		{
			(*temp) = (*stack);
			value = (*stack)->data;
			(*stack) = (*stack)->next;
		}
		else if (value <= (*stack)->data || (*stack)->index != 0)
			(*stack) = (*stack)->next;
	}
}

void	stack_position(t_stack **stack)

{
	int		i;
	t_stack	*head;

	i = 1;
	head = (*stack);
	while (*stack)
	{
		(*stack)->position = i;
		(*stack) = (*stack)->next;
		i++;
	}
	(*stack) = head;
}

void	stack_sign(t_stack **stack)

{
	t_stack	*head;
	int		length;
	int		mid;

	if (!*stack)
		return ;
	head = (*stack);
	length = ft_lilast(*stack)->position;
	mid = length / 2 + length % 2;
	while (*stack)
	{
		if ((*stack)->position <= mid)
			(*stack)->sign = '+';
		else
			(*stack)->sign = '-';
		(*stack) = (*stack)->next;
	}
	(*stack) = head;
}
