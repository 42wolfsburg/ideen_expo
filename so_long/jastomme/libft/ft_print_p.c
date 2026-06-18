/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:01:14 by jastomme          #+#    #+#             */
/*   Updated: 2024/09/24 14:07:15 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_p(void *ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (ft_print_s("(nil)"));
	i = i + ft_print_s("0x");
	i = i + ft_print_ptr((unsigned long)ptr, 16);
	return (i);
}
