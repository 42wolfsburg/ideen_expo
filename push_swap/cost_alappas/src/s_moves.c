/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:30:03 by alappas           #+#    #+#             */
/*   Updated: 2023/09/14 18:56:58 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa_sb(t_stack **stack)

{
	t_stack	*head;
	t_stack	*second;

	if ((*stack) == NULL || (*stack)->next == NULL)
		return ;
	head = (*stack);
	second = (*stack)->next->next;
	(*stack) = (*stack)->next;
	(*stack)->next = head;
	head->next = second;
	stack_position(stack);
}

void	sa(t_stack **stack_a)

{
	sa_sb(stack_a);
	ft_printf("sa\n");
}

void	sb(t_stack **stack_b)

{
	sa_sb(stack_b);
	ft_printf("sb\n");
}

void	ss(t_stack **stack_a, t_stack **stack_b)

{
	sa_sb(stack_a);
	sa_sb(stack_b);
	ft_printf("ss\n");
}
