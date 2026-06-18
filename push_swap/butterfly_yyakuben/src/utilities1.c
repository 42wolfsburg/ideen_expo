/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:57:07 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/29 00:19:51 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

long	ft_atoi_num(const char *str)
{
	long			num;
	int				i;
	long			np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			np = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (np * num);
}

int	is_sorted(t_lists **lst)
{
	t_lists	*head;

	head = *lst;
	while ((*lst)->next)
	{
		if ((*lst)->content < (*lst)->next->content)
		{
			*lst = (*lst)->next;
		}
		else
		{
			*lst = head;
			return (0);
		}
	}
	(*lst) = head;
	return (1);
}

int	ft_lst_size(t_lists **lst)
{
	t_lists	*head;
	int		i;

	i = 0;
	head = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		i++;
	}
	*lst = head;
	return (i);
}

int	find_min(t_lists **lst)
{
	t_lists	*tmp;
	int		min;

	min = INT_MAX;
	tmp = *lst;
	while (*lst)
	{
		if ((*lst)->content <= min && (*lst)->index == -1)
		{
			min = (*lst)->content;
		}
		*lst = (*lst)->next;
	}
	*lst = tmp;
	return (min);
}

int	find_max(t_lists **lst)
{
	t_lists	*tmp;
	int		max;

	max = INT_MIN;
	tmp = *lst;
	while (*lst)
	{
		if (max <= (*lst)->content)
		{
			max = (*lst)->content;
		}
		*lst = (*lst)->next;
	}
	*lst = tmp;
	return (max);
}
