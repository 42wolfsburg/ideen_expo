/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:00:46 by alappas           #+#    #+#             */
/*   Updated: 2023/09/27 01:52:00 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*ft_prelilast(t_stack *list)

{
	if (list != NULL)
	{
		while (list->next->next != NULL)
			list = list->next;
	}
	return (list);
}

void	ft_listclear(t_stack **stack)

{
	t_stack	*head;

	while (*stack)
	{
		head = (*stack)->next;
		free(*stack);
		(*stack) = head;
	}
}

int	node_max(t_stack **stack)

{
	int		value;
	t_stack	*temp;

	value = (*stack)->data;
	temp = (*stack);
	while (temp)
	{
		if (value < temp->data)
		{
			value = temp->data;
			temp = temp->next;
		}
		else if (value >= temp->data)
			temp = temp->next;
	}
	return (value);
}

int	node_min(t_stack **stack)

{
	int		value;
	t_stack	*temp;

	value = (*stack)->data;
	temp = (*stack);
	while (temp)
	{
		if (value > temp->data)
		{
			value = temp->data;
			temp = temp->next;
		}
		else if (value <= temp->data)
			temp = temp->next;
	}
	return (value);
}

int	sort_check_a(t_stack *stack_a)

{
	while (stack_a->next != NULL)
	{
		if (stack_a->data < stack_a->next->data)
			stack_a = stack_a->next;
		else
			return (1);
	}
	return (0);
}
