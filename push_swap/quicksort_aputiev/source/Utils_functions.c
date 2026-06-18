/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:44:29 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:44:13 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"
#include <stdlib.h>

//takes pointer to the 1st char from av[i] (the number) and
// pointer to the 1st int from stack a;
//pass tabs; checks sign; checks if it is a digit; checks int limits;
//returns a signed number;
int	push_swap_atoi(char *str, int *stack)
{
	unsigned int		i;
	int					sign;
	unsigned long int	number;

	i = 0;
	number = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error_detected(stack);
		number = (str[i] - '0') + (number * 10);
		i++;
	}
	if ((number > 2147483648 && sign == -1)
		|| (number > 2147483647 && sign == 1))
		error_detected(stack);
	return (number * sign);
}
// calculate quantity of entered numbers for sorting:

int	push_swap_strlen(char **av)
{
	int	i;

	i = 0;
	while (*av)
	{
		av++;
		i++;
	}
	return (i);
}

/*checks if numbers already sorted or not-sorted
with order==0:
	-returns 0 if not-sorted
	-returns 1 if already sorted*/
int	check_sorted(int *stack, int size, int order)
{
	int	i;

	if (order == 0)
	{
		i = 1;
		while (i < size)
		{
			if (stack[i - 1] > stack[i])
				return (0);
			i++;
		}
		return (1);
	}
	else
	{
		i = 1;
		while (i < size)
		{
			if (stack[i - 1] < stack[i])
				return (0);
			i++;
		}
		return (1);
	}
}
//check duplicates:

void	check_doubles(int *stack, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < size)
	{
		while (j < size)
		{
			if (stack[i] == stack[j])
				error_detected(stack);
			j++;
		}
		i++;
		j = i + 1;
	}
}

/*frees memory, prints an error, and stops the program*/
void	error_detected(int *stack)
{
	free(stack);
	ft_printf("Error\n");
	exit (1);
}
