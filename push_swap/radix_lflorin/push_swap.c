/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorin <lflorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 19:24:22 by lflorin           #+#    #+#             */
/*   Updated: 2026/05/29 11:00:51 by lflorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	handle_tokens(char **tokens, t_stack **stack_a)
{
	int	j;

	j = 0;
	while (tokens[j])
	{
		if (process_token(tokens[j], stack_a))
			return (1);
		j++;
	}
	return (0);
}

static int	parse_arguments(int argc, char **argv, t_stack **stack_a)
{
	char	**tokens;
	int		i;

	i = 1;
	while (i < argc)
	{
		tokens = ft_split_spaces(argv[i]);
		if (!tokens)
			return (1);
		if (handle_tokens(tokens, stack_a))
		{
			free_split(tokens);
			return (1);
		}
		free_split(tokens);
		i++;
	}
	return (0);
}

static void	init_stacks(t_stack **stack_a, t_stack **stack_b)
{
	*stack_a = NULL;
	*stack_b = NULL;
}

int	calling_function(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	if (!stack_a || !(*stack_a) || is_sorted(*stack_a))
		return (0);
	size = ft_lstsize (*stack_a);
	if (size == 2)
		sort_2 (stack_a);
	else if (size == 3)
		sort_3 (stack_a);
	else if (size <= 5)
		sort_5 (stack_a, stack_b);
	else
	{
		assign_indexes(*stack_a);
		radix_sort(stack_a, stack_b);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	init_stacks(&stack_a, &stack_b);
	if (argc <= 1)
		return (0);
	if (parse_arguments(argc, argv, &stack_a))
	{
		free_all(&stack_a);
		return (1);
	}
	calling_function(&stack_a, &stack_b);
	free_all(&stack_a);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_stack	*stack_a;
// 	t_stack	*stack_b;
// 	char	**tokens;
// 	int		i;
// 	int		j;

// 	stack_a = NULL;
// 	stack_b = NULL;
// 	if (argc <= 1)
// 		return (0);
// 	i = 1;
// 	while (i < argc)
// 	{
// 		tokens = ft_split_spaces(argv[i]);
// 		if (!tokens)
// 			return (1);
// 		j = 0;
// 		while (tokens[j])
// 		{
// 			if (process_token(tokens[j], &stack_a))
// 			{
// 				free_split(tokens);
// 				free_all(&stack_a);
// 				return (1);
// 			}
// 			j++;
// 		}
// 		free_split(tokens);
// 		i++;
// 	}
// 	calling_function(&stack_a, &stack_b);
// 	free_all(&stack_a);
// 	return (0);
// }