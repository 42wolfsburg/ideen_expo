/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:45:24 by alappas           #+#    #+#             */
/*   Updated: 2023/09/14 18:56:47 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ra_rb(t_stack **stack)

{
	t_stack	*head;
	t_stack	*bottom;

	head = (*stack);
	(*stack) = (*stack)->next;
	bottom = ft_lilast(*stack);
	head->next = NULL;
	bottom->next = head;
	stack_position(stack);
}

void	ra(t_stack **stack_a)

{
	ra_rb(stack_a);
	ft_printf("ra\n");
}

void	rb(t_stack **stack_b)

{
	ra_rb(stack_b);
	ft_printf("rb\n");
}

void	rr(t_stack **stack_a, t_stack **stack_b)

{
	ra_rb(stack_a);
	ra_rb(stack_b);
	ft_printf("rr\n");
}
