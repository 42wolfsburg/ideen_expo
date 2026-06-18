/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:26:50 by lflorin           #+#    #+#             */
/*   Updated: 2026/05/28 14:28:48 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*temp;

	if (!*stack_a)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)-> next;
	temp -> next = (*stack_b);
	*stack_b = temp;
}

void	pb(t_stack **stack_a, t_stack **stack_b)
{
	push (stack_a, stack_b);
	write (1, "pb\n", 3);
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push (stack_b, stack_a);
	write (1, "pa\n", 3);
}
