/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:59:25 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 14:34:42 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_newlist(int content)
{
	t_stack	*element;

	element = malloc(sizeof(t_stack));
	if (!element)
		return (NULL);
	element -> value = content;
	element -> next = NULL;
	return (element);
}

t_stack	*ft_last(t_stack *stack_a)
{
	t_stack	*temp;

	if (!stack_a)
		return (NULL);
	temp = stack_a;
	while (temp ->next)
		temp = temp ->next;
	return (temp);
}
