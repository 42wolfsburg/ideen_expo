/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:41:45 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 13:08:51 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

int	is_valid_input(char *string)
{
	unsigned int	i;

	i = 0;
	if (!string || !string[0])
		return (0);
	if (string[i] == '+' || string[i] == '-')
		i++;
	if (!string[i])
		return (0);
	while (string[i])
	{
		if (string[i] < '0' || string[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
