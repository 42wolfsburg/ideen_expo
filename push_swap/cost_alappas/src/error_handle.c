/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:45:56 by alappas           #+#    #+#             */
/*   Updated: 2024/04/14 01:05:12 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	dup_handle(char **argv)

{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_strcmp(argv[i], argv[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	symbol_handle(char **argv)

{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == 45 && j == 0)
				j++;
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			else
				j++;
		}
		i++;
	}
	return (0);
}

int	int_handle(char **argv)

{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_toi(argv[i]) > INT_MAX || ft_toi(argv[i]) < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

int	zero_handle(char **argv)

{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[1][0] == '\0')
			return (1);
		if (argv[i][0] == '0' && argv[i][1])
			return (1);
		else if (argv[i][0] == '-' && argv[i][1] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	error_handle(char **argv)
{
	if (zero_handle(argv) == 1 || int_handle(argv) == 1 || dup_handle(argv) == 1
		|| symbol_handle(argv) == 1)
	{
		if (write(2, "Error\n", 6) == -1)
			exit(1);
		exit(1);
	}
	return (0);
}
