/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorin <lflorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:39:13 by lea               #+#    #+#             */
/*   Updated: 2026/05/29 11:06:06 by lflorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_putstr(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_lstsize(t_stack *lst)
{
	int		i;
	t_stack	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp-> next;
	}
	return (i);
}

int	is_sorted(t_stack *stack_a)
{
	while (stack_a && stack_a-> next)
	{
		if (stack_a-> value > stack_a-> next-> value)
			return (0);
		stack_a = stack_a-> next;
	}
	return (1);
}

int	dublicate_check(t_stack *stack_a, long int value)
{
	while (stack_a)
	{
		if (stack_a->value == value)
			return (1);
		stack_a = stack_a->next;
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
