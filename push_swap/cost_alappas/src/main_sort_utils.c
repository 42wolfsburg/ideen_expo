/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 01:57:17 by alappas           #+#    #+#             */
/*   Updated: 2024/04/14 01:07:55 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	stack_cost_a(t_stack **stack_a)
{
	t_stack	*head;
	int		final_plus;

	stack_sign(stack_a);
	stack_index(stack_a, ft_lilast(*stack_a)->position + 1);
	head = (*stack_a);
	final_plus = 0;
	while (*stack_a)
	{
		if ((*stack_a)->sign == '+')
		{
			(*stack_a)->initial_cost = (*stack_a)->position - 1;
			final_plus = (*stack_a)->position;
			(*stack_a) = (*stack_a)->next;
		}
		else if ((*stack_a)->sign == '-')
		{
			(*stack_a)->initial_cost = final_plus - 1;
			final_plus -= 1;
			(*stack_a) = (*stack_a)->next;
		}
	}
	(*stack_a) = head;
}

void	stack_cost_b(t_stack **stack_b)
{
	t_stack	*head;
	int		final_plus;

	stack_sign(stack_b);
	stack_index(stack_b, ft_lilast(*stack_b)->position + 1);
	head = (*stack_b);
	final_plus = 0;
	while (*stack_b)
	{
		if ((*stack_b)->sign == '+')
		{
			(*stack_b)->initial_cost = (*stack_b)->position - 1;
			final_plus = (*stack_b)->position;
			(*stack_b) = (*stack_b)->next;
		}
		else if ((*stack_b)->sign == '-')
		{
			(*stack_b)->initial_cost = final_plus
				- ft_lilast((*stack_b))->position % 2;
			final_plus -= 1;
			(*stack_b) = (*stack_b)->next;
		}
	}
	(*stack_b) = head;
}

void	double_rotate(t_stack *inner_node, t_stack *target_node,
	t_stack **stack_a, t_stack **stack_b)

{
	int	i;
	int	a_cost;
	int	b_cost;

	i = 0;
	a_cost = inner_node->initial_cost;
	b_cost = target_node->initial_cost;
	if (inner_node->sign != target_node->sign)
		return ;
	if (a_cost == b_cost)
		i = inner_node->initial_cost;
	else if (a_cost > b_cost)
		i = b_cost;
	else if (a_cost < b_cost)
		i = a_cost;
	while (i != 0)
	{
		if (inner_node->sign == '-')
			rrr(stack_a, stack_b);
		else if (inner_node->sign == '+')
			rr(stack_a, stack_b);
		i--;
	}
}

void	stack_final_cost_helper(t_stack **stack_a, t_stack **stack_b,
	t_stack **target_node, t_stack *head_a)

{
	(*stack_b)->final_cost = (*target_node)->initial_cost
		+ (*stack_b)->initial_cost;
	(*stack_b)->target_pos = (*target_node)->position;
	(*stack_b) = (*stack_b)->next;
	(*stack_a) = head_a;
}

void	inside_push_helper(t_stack **stack_a, t_stack **stack_b,
	t_stack *target_node, t_stack *inner_node)

{
	while (target_node->data != (*stack_b)->data)
	{
		if (target_node->sign == '-')
			rrb(stack_b);
		else if (target_node->sign == '+')
			rb(stack_b);
	}
	while (inner_node->data != (*stack_a)->data)
	{
		if (inner_node->sign == '-')
			rra(stack_a);
		else if (inner_node->sign == '+')
			ra(stack_a);
	}
}
