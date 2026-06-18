/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:26:54 by lflorin           #+#    #+#             */
/*   Updated: 2026/05/28 14:18:48 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **r)
{
	t_stack	*temp;
	t_stack	*old_head;

	if (!r || !*r || !(*r)-> next)
	{
		return ;
	}
	old_head = *r;
	temp = *r;
	while (temp -> next)
		temp = temp -> next;
	temp -> next = *r;
	*r = (*r)-> next;
	old_head -> next = NULL;
}

void	ra(t_stack **r)
{
	rotate (r);
	write (1, "ra\n", 3);
}

void	rb(t_stack **r)
{
	rotate (r);
	write (1, "rb\n", 3);
}

void	rr(t_stack **ra, t_stack **rb)
{
	rotate (ra);
	rotate (rb);
	write (1, "rr\n", 3);
}
