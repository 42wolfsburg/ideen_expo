/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_upper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:15:18 by jastomme          #+#    #+#             */
/*   Updated: 2024/09/24 14:07:04 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_d_upper(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789ABCDEF";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_d_upper(-n, base) + 1);
	}
	else if (n < base)
		return (ft_print_c(symbols[n]));
	else
	{
		count = ft_print_d_upper(n / base, base);
		return (count + ft_print_d_upper(n % base, base));
	}
}
