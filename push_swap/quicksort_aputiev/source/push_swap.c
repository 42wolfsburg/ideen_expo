/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:19:21 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 12:11:33 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include "../printf/ft_printf.h"
#include <stdlib.h>

// this is the main process function.
//stack contains stacks a and b;

void	push_swap(char **av)
{
	t_stacks	stack;
	int			size;
	int			i;

	i = -1;
	size = push_swap_strlen(av);
	stack.a = malloc(size * sizeof(int));
	if (!stack.a)
		return ;
	stack.size_a = size;
	stack.b = malloc(size * sizeof(int));
	if (!stack.b)
	{
		free(stack.a);
		return ;
	}
	stack.size_b = 0;
	while (++i < size)
		stack.a[i] = push_swap_atoi(av[i], stack.a);
	check_doubles(stack.a, size);
	sort(&stack, size);
	free(stack.a);
	free(stack.b);
}

//-------------------------------------------------------------------------
//Main function just checks input data and runs push_swap process function:
int	main(int ac, char **av)
{
	if (ac > 1)
	{
		av++;
		if (ac == 2)
			av = ft_split(*av, ' ');
		push_swap(av);
		return (0);
	}
	return (0);
}
