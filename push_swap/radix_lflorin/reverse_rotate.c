/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:39:09 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 14:20:34 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack **rr)
{
	t_stack	*temp;
	t_stack	*new_last;
	t_stack	*new_first;

	if (!rr || !*rr || !(*rr)-> next)
		return ;
	temp = (*rr);
	while (temp -> next && temp -> next -> next)
	{
		temp = temp -> next;
	}
	new_last = temp;
	new_first = temp -> next;
	new_last -> next = NULL;
	new_first -> next = (*rr);
	*rr = new_first;
}

void	rra(t_stack **r)
{
	reverse_rotate (r);
	write (1, "rra\n", 4);
}

void	rrb(t_stack **r)
{
	reverse_rotate (r);
	write (1, "rrb\n", 4);
}

void	rrr(t_stack **rra, t_stack **rrb)
{
	reverse_rotate (rra);
	reverse_rotate (rrb);
	write (1, "rrr\n", 4);
}
