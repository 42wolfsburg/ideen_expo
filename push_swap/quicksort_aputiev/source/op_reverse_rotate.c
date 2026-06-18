/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:57:07 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:57:23 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"

// -----------------------------------------------------------------------
/*do reverse rotate operation (rra) in the stack a;
--------
Example:
2
1
3
_ _
a b
--------
Exec rra:
3
2
1
_ _
a b
--------
*/
void	reverse_rotate_a(t_stacks *stack, int bonus)
{
	int	tmp;
	int	i;

	if (stack->size_a == 0 || stack->size_a == 1)
		return ;
	i = stack->size_a - 1;
	tmp = stack->a[i];
	while (i)
	{
		stack->a[i] = stack->a[i - 1];
		i--;
	}
	stack->a[i] = tmp;
	if (!bonus)
		ft_printf("rra\n");
}

// --------------------------------------------------------------------
//do reverse rotate operation (rrb) in the stack b;
void	reverse_rotate_b(t_stacks *stack, int bonus)
{
	int	tmp;
	int	i;

	if (stack->size_b == 0 || stack->size_b == 1)
		return ;
	i = stack->size_b - 1;
	tmp = stack->b[i];
	while (i)
	{
		stack->b[i] = stack->b[i - 1];
		i--;
	}
	stack->b[i] = tmp;
	if (!bonus)
		ft_printf("rrb\n");
}

// --------------------------------------------------------------
//do reverse rotate operations (rra and rrb) in the stacks a and b;
void	reverse_rotate_r(t_stacks *stack, int bonus)
{
	int	tmp;
	int	i;

	if (stack->size_a == 0 || stack->size_a == 1
		|| (stack->size_b == 0 || stack->size_b == 1))
		return ;
	i = stack->size_a - 1;
	tmp = stack->a[i];
	while (i)
	{
		stack->a[i] = stack->a[i - 1];
		i--;
	}
	stack->a[i] = tmp;
	i = stack->size_b - 1;
	tmp = stack->b[i];
	while (i--)
		stack->b[i] = stack->b[i - 1];
	stack->b[i] = tmp;
	if (!bonus)
		ft_printf("rrr\n");
}
