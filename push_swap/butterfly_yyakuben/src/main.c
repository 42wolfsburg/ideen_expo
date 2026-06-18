/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 19:25:21 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/29 15:43:31 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	simple_sort(t_lists **stack_a, t_lists **stack_b, int ac)
{
	if (ac == 3)
		sort2(stack_a);
	else if (ac == 4)
		sort3(stack_a);
	else if (ac == 5)
		sort4(stack_a, stack_b);
	else if (ac == 6)
		sort5(stack_a, stack_b);
}

int	main(int ac, char **av)
{
	t_lists	*stack_a;
	t_lists	*stack_b;

	stack_a = init_stack_a(ac, av);
	stack_b = NULL;
	if (!stack_a)
		return (0);
	if (is_sorted(&stack_a))
		return (ft_listclear(&stack_a), 0);
	if (ac <= 6)
		simple_sort(&stack_a, &stack_b, ac);
	else
	{
		find_index(&stack_a);
		big_sort(&stack_a, &stack_b, ac);
		while (stack_b)
		{
			go_home(&stack_b);
			pa(&stack_a, &stack_b);
		}
	}
	return (ft_listclear(&stack_a), 0);
}
