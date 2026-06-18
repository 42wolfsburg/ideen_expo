/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:26:57 by lflorin           #+#    #+#             */
/*   Updated: 2026/05/28 14:10:30 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack **s)
{
	t_stack	*first;
	t_stack	*second;

	if (!s || !*s || !(*s)-> next)
	{
		return ;
	}
	first = *s;
	second = first -> next;
	first -> next = second -> next;
	second -> next = first;
	*s = second;
}

void	sa(t_stack **stack_a)
{
	swap (stack_a);
	write (1, "sa\n", 3);
}

void	sb(t_stack **stack_b)
{
	swap (stack_b);
	write (1, "sb\n", 3);
}

void	ss(t_stack **stack_a, t_stack **stack_b)//not sure about all this yet
{
	swap (stack_a);
	swap (stack_b);
	write (1, "ss\n", 3);
}
