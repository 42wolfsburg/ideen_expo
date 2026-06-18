/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:32:09 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/16 09:40:29 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	parse_arg(char *arg, t_stack_node **a, char **args, int argc)
{
	long	val;

	check_numeric(arg, a, args, argc);
	val = ft_atoi(arg);
	check_overflow(val, a, args, argc);
	add((int)val, a);
}

static char	**get_args(int argc, char **argv)
{
	char	**args;

	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv;
	if (!args)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (args);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	init_stacks(int argc, char **argv, t_stack_node **a)
{
	int		i;
	char	**args;

	args = get_args(argc, argv);
	if (argc == 2)
		i = 0;
	else
		i = 1;
	while (args[i])
	{
		parse_arg(args[i], a, args, argc);
		i++;
	}
	check_duplicates(a, args, argc);
	if (argc == 2)
		free_args(args);
}
