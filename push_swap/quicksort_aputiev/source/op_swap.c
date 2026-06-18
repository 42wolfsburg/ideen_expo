/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:57:58 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:58:07 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"

/*do swap_a (sa) operation:
--------
Example:
2
1
3
_ _
a b
--------
Exec sa:
1
2
3
_ _
a b
--------
*/
void	swap_a(t_stacks *stack, int bonus)
{
	int	tmp;

	if (stack->size_a == 0 || stack->size_a == 1)
		return ;
	tmp = 0;
	tmp = stack->a[0];
	stack->a[0] = stack->a[1];
	stack->a[1] = tmp;
	if (!bonus)
		ft_printf("sa\n");
}

// ------------------------------------------------------------------
//do swap_b (sb) operation;

void	swap_b(t_stacks *stack, int bonus)
{
	int	tmp;

	if (stack->size_b == 0 || stack->size_b == 1)
		return ;
	tmp = 0;
	tmp = stack->b[0];
	stack->b[0] = stack->b[1];
	stack->b[1] = tmp;
	if (!bonus)
		ft_printf("sb\n");
}

// -------------------------------------------------------------
//do swap_a and swap_b operations togeteher;
void	swap_s(t_stacks *stack, int bonus)
{
	int	tmp;

	if (stack->size_a == 0 || stack->size_a == 1
		|| (stack->size_b == 0 || stack->size_b == 1))
		return ;
	tmp = 0;
	tmp = stack->a[0];
	stack->a[0] = stack->a[1];
	stack->a[1] = tmp;
	tmp = stack->b[0];
	stack->b[0] = stack->b[1];
	stack->b[1] = tmp;
	if (!bonus)
		ft_printf("ss\n");
}
