/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:43:19 by aputiev           #+#    #+#             */
/*   Updated: 2023/03/11 11:10:34 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../printf/ft_printf.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	free_error(t_stacks *stack, int choix)
{
	free(stack->a);
	free(stack->b);
	if (choix)
		ft_printf("Error\n");
	exit(1);
}

void	exec_instruction(t_stacks *stack, char *instruction)
{
	if (ft_strcmp(instruction, "sa\n") == 0)
		swap_a(stack, 1);
	else if (!ft_strcmp(instruction, "sb\n"))
		swap_b(stack, 1);
	else if (!ft_strcmp(instruction, "ss\n"))
		swap_s(stack, 1);
	else if (!ft_strcmp(instruction, "ra\n"))
		rotate_a(stack, 1);
	else if (!ft_strcmp(instruction, "rb\n"))
		rotate_b(stack, 1);
	else if (!ft_strcmp(instruction, "rr\n"))
		rotate_r(stack, 1);
	else if (!ft_strcmp(instruction, "rra\n"))
		reverse_rotate_a(stack, 1);
	else if (!ft_strcmp(instruction, "rrb\n"))
		reverse_rotate_b(stack, 1);
	else if (!ft_strcmp(instruction, "rrr\n"))
		reverse_rotate_r(stack, 1);
	else if (!ft_strcmp(instruction, "pa\n"))
		push_a(stack, 1);
	else if (!ft_strcmp(instruction, "pb\n"))
		push_b(stack, 1);
	else
		free_error(stack, 1);
}

void	scan_from_stdin(t_stacks *stack)
{
	char		*instruction;

	instruction = get_next_line(0);
	while (instruction && (*instruction != '\n'))
	{
		exec_instruction(stack, instruction);
		free(instruction);
		instruction = get_next_line(0);
	}
	if (check_sorted(stack->a, stack->size_a, 0) && stack->size_b == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_error(stack, 0);
}

int	*c_errors(char **av)
{
	int	*a;
	int	size;
	int	i;

	i = -1;
	size = push_swap_strlen(av);
	a = malloc(size * sizeof(int));
	while (++i < size)
		a[i] = push_swap_atoi(av[i], a);
	check_doubles(a, size);
	return (a);
}

int	main(int ac, char **av)
{
	t_stacks	stack;

	if (ac > 1)
	{
		av++;
		if (ac == 2)
			av = ft_split(*av, ' ');
		stack.a = c_errors(av);
		stack.size_a = push_swap_strlen(av);
		stack.b = malloc(stack.size_a * sizeof(int));
		if (!stack.b)
		{
			free(stack.a);
			return (0);
		}
		stack.size_b = 0;
		scan_from_stdin(&stack);
	}
	return (0);
}
