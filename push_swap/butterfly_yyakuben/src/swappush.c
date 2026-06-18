/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swappush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:23:45 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/26 18:00:13 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_lists **lst)
{
	lst_swap(lst);
	ft_printf("sa\n");
}

void	sb(t_lists **lst)
{
	lst_swap(lst);
	ft_printf("sb\n");
}

void	ss(t_lists **lst_a, t_lists **lst_b)
{
	lst_swap(lst_a);
	lst_swap(lst_b);
	ft_printf("ss\n");
}

void	pa(t_lists **lst_b, t_lists **lst_a)
{
	push(lst_a, lst_b);
	ft_printf("pa\n");
}

void	pb(t_lists **lst_a, t_lists **lst_b)
{
	push(lst_b, lst_a);
	ft_printf("pb\n");
}
