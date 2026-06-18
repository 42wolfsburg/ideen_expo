/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:30:15 by alappas           #+#    #+#             */
/*   Updated: 2024/04/14 01:40:36 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	main(int argc, char **argv)

{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	error_handle(argv);
	stack_a = parse_elements(argv);
	stack_b = NULL;
	stack_index(&stack_a, argc);
	if (sort_check_a(stack_a) == 0)
	{
		ft_listclear(&stack_a);
		return (0);
	}
	if (argc <= 6)
		all_moves(argc, &stack_a, &stack_b);
	else
		main_sort(&stack_a, &stack_b);
	ft_listclear(&stack_a);
	return (0);
}

void	all_moves(int argc, t_stack **stack_a, t_stack **stack_b)
{
	if (argc == 3)
		two_digits(stack_a);
	if (argc == 4)
		three_digits(stack_a);
	if (argc == 5)
		four_digits(stack_a, stack_b);
	if (argc == 6)
		five_digits(stack_a, stack_b);
}
