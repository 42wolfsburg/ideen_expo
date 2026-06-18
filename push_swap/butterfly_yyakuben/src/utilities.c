/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:20:38 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/28 22:18:59 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	check_duplicate(t_lists *stack_a, int num)
{
	if (!stack_a)
		return (1);
	while (stack_a)
	{
		if (stack_a->content == num)
			return (0);
		stack_a = stack_a->next;
	}
	return (1);
}

int	check_max_min(long num)
{
	if (num > 2147483647 || num < -2147483648)
		return (0);
	return (1);
}

int	ft_str_is_num(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[0]) || ((str[0] == '+' || str[0] == '-') && str[1]))
	{
		while (str[i])
		{
			if (!(ft_isdigit(str[i])))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

t_lists	*init_stack_a(int ac, char **av)
{
	t_lists	*head;
	int		i;
	long	num;

	(void)ac;
	i = 1;
	head = NULL;
	while (av[i])
	{
		if (ft_str_is_num(av[i]))
		{
			num = ft_atoi_num(av[i]);
			if (!check_max_min(num) || !check_duplicate(head, num))
				print_error();
			if (!head)
				head = ft_lstnew(num);
			else
				ft_lstadd_back(&head, ft_lstnew(num));
		}
		else
			print_error();
		i++;
	}
	return (head);
}
