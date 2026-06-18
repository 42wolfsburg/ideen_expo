/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:30:02 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:48:11 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"

/*do push_a (pa) operation*/

void	push_a(t_stacks *stack, int bonus)
{
	int	i;

	if (stack->size_b)
	{
		stack->size_a++;
		i = stack->size_a;
		while (--i > 0)
			stack->a[i] = stack->a[i - 1];
		stack->a[0] = stack->b[0];
		i = -1;
		stack->size_b--;
		while (++i < stack->size_b)
			stack->b[i] = stack->b[i + 1];
		if (!bonus)
			ft_printf("pa\n");
	}
	else
		return ;
}

/*
do push_b (pb operation);
--------
Example:
2
1
3
_ _
a b
--------
Exec pb:
1 2
3
_ _
a b
--------
*/

void	push_b(t_stacks *stack, int bonus)
{
	int	i;

	if (stack->size_a)
	{
		stack->size_b++;
		i = stack->size_b;
		while (--i > 0)
			stack->b[i] = stack->b[i - 1];
		stack->b[0] = stack->a[0];
		i = -1;
		stack->size_a--;
		while (++i < stack->size_a)
			stack->a[i] = stack->a[i + 1];
		if (!bonus)
			ft_printf("pb\n");
	}
	else
		return ;
}

// -------------------------------------------------------------------------
// run push_a or push_b
int	ft_push(t_stacks *stack, int len, int push)
{
	if (push == 0)
		push_b(stack, 0);
	else
		push_a(stack, 0);
	len--;
	return (len);
}
