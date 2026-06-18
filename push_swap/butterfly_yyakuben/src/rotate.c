/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:58:15 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/18 19:55:30 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ra(t_lists **lst)
{
	lst_rotate(lst);
	ft_printf("ra\n");
}

void	rb(t_lists **lst)
{
	lst_rotate(lst);
	ft_printf("rb\n");
}

void	rr(t_lists **lst_a, t_lists **lst_b)
{
	lst_rotate(lst_a);
	lst_rotate(lst_b);
	ft_printf("rr\n");
}
