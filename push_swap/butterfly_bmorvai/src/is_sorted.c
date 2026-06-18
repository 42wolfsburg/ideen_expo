/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:12 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 14:55:16 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_sorted(t_stack_node **a)
{
	t_stack_node	*current;
	int				current_value;

	current = *a;
	while (current->next != 0)
	{
		current_value = current->value;
		current = current->next;
		if (current_value > current->value)
			return (0);
	}
	return (1);
}
