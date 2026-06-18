/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:45:35 by alappas           #+#    #+#             */
/*   Updated: 2023/09/14 18:56:52 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rra_rrb(t_stack **stack)

{
	t_stack	*bottom;
	t_stack	*prebottom;

	bottom = ft_lilast(*stack);
	prebottom = ft_prelilast(*stack);
	bottom->next = (*stack);
	(*stack) = bottom;
	prebottom->next = NULL;
	stack_position(stack);
}

void	rra(t_stack **stack_a)

{
	rra_rrb(stack_a);
	ft_printf("rra\n");
}

void	rrb(t_stack **stack_b)

{
	rra_rrb(stack_b);
	ft_printf("rrb\n");
}

void	rrr(t_stack **stack_a, t_stack **stack_b)

{
	rra_rrb(stack_a);
	rra_rrb(stack_b);
	ft_printf("rrr\n");
}
