/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:17 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 13:35:12 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pb(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*tmp;

	if (*a == NULL)
		return ;
	tmp = *a;
	*a = (*a)->next;
	tmp->next = *b;
	*b = tmp;
	write(1, "pb\n", 3);
}

void	pa(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*tmp;

	if (*b == NULL)
		return ;
	tmp = *b;
	*b = (*b)->next;
	tmp->next = *a;
	*a = tmp;
	write(1, "pa\n", 3);
}

// int main(void)
// {
//     t_stack_node *a;
//     t_stack_node *b;
//     int external_value;

//     external_value = 7;
//     a = malloc(sizeof(t_stack_node));
//     a->value = external_value;
//     a->next = NULL;
//     b = NULL;
//     push(&a, &b);
//     printf("%d", b->value);
// }