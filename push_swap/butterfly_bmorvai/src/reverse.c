/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:29 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 13:47:24 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ra(t_stack_node **a)
{
	t_stack_node	*tmp;
	t_stack_node	*first;

	first = *a;
	tmp = *a;
	(*a) = tmp->next;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	first->next = NULL;
	tmp->next = first;
	write(1, "ra\n", 3);
}

void	rb(t_stack_node **b)
{
	t_stack_node	*tmp;
	t_stack_node	*first;

	first = *b;
	tmp = *b;
	(*b) = tmp->next;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	first->next = NULL;
	tmp->next = first;
	write(1, "rb\n", 3);
}

void	rr(t_stack_node **a, t_stack_node **b)
{
	ra(a);
	rb(b);
	write(1, "rr\n", 3);
}

void	rra(t_stack_node **a)
{
	t_stack_node	*tmp;
	t_stack_node	*last;

	tmp = *a;
	while (tmp->next->next != NULL)
	{
		tmp = tmp->next;
	}
	last = tmp->next;
	tmp->next = NULL;
	last->next = *a;
	*a = last;
	write(1, "rra\n", 4);
}

void	rrb(t_stack_node **b)
{
	t_stack_node	*tmp;
	t_stack_node	*last;

	tmp = *b;
	while (tmp->next->next != NULL)
	{
		tmp = tmp->next;
	}
	last = tmp->next;
	tmp->next = NULL;
	last->next = *b;
	*b = last;
	write(1, "rrb\n", 4);
}

// Function Reverse Rotate Both is Usable but Not Used in This Approach
// void	rrr(t_stack_node **a, t_stack_node **b)
// {
// 	rra(a);
// 	rrb(b);
// 	write(1, "rrr\n", 4);
// }
