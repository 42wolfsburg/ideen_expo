/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverserotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:17:20 by yyakuben          #+#    #+#             */
/*   Updated: 2024/04/17 19:23:00 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rra(t_lists **lst)
{
	lst_reverse_rotate(lst);
	ft_printf("rra\n");
}

void	rrb(t_lists **lst)
{
	lst_reverse_rotate(lst);
	ft_printf("rrb\n");
}

void	rrr(t_lists **lst_a, t_lists **lst_b)
{
	lst_reverse_rotate(lst_a);
	lst_reverse_rotate(lst_b);
	ft_printf("rrr\n");
}
