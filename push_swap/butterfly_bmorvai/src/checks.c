/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:04 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/16 08:50:33 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	check_numeric(char *argument, t_stack_node **a, char **args, int argc)
{
	int	i;

	i = 0;
	if (argument[0] == '-' || argument[0] == '+')
		i = 1;
	if (argument[i] == '\0')
	{
		if (argc == 2)
			free_args(args);
		write(2, "Error\n", 6);
		exit(1);
	}
	while (argument[i])
	{
		if (!ft_isdigit(argument[i]))
		{
			if (argc == 2)
				free_args(args);
			free_stack(a);
			write(2, "Error\n", 6);
			exit(1);
		}
		i++;
	}
}

void	check_overflow(long number, t_stack_node **a, char **args, int argc)
{
	if (INT_MIN > number || number > INT_MAX)
	{
		if (argc == 2)
			free_args(args);
		free_stack(a);
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	check_duplicates(t_stack_node **stack, char **args, int argc)
{
	t_stack_node	*current;
	t_stack_node	*checker;

	current = *stack;
	while (current)
	{
		checker = current->next;
		while (checker)
		{
			if (checker->value == current->value)
			{
				if (argc == 2)
					free_args(args);
				free_stack(stack);
				write(2, "Error\n", 6);
				exit(1);
			}
			checker = checker->next;
		}
		current = current->next;
	}
}
