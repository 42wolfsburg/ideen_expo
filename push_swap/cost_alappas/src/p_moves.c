/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_moves.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:44:56 by alappas           #+#    #+#             */
/*   Updated: 2024/04/26 00:58:03 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pa_pb(t_stack **stack_dest, t_stack **stack_source)

{
	t_stack	*data;

	if ((*stack_source) == NULL)
		return ;
	data = (*stack_dest);
	(*stack_dest) = (*stack_source);
	if (*stack_source)
		(*stack_source) = (*stack_source)->next;
	(*stack_dest)->next = data;
	stack_position(stack_source);
	stack_position(stack_dest);
}

void	pa(t_stack **stack_a, t_stack **stack_b)

{
	pa_pb(stack_a, stack_b);
	ft_printf("pa\n");
}

void	pb(t_stack **stack_a, t_stack **stack_b)

{
	pa_pb(stack_b, stack_a);
	ft_printf("pb\n");
}
