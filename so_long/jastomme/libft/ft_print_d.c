/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:13:25 by jastomme          #+#    #+#             */
/*   Updated: 2024/09/24 14:07:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_d(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_d(-n, base) + 1);
	}
	else if (n < base)
		return (ft_print_c(symbols[n]));
	else
	{
		count = ft_print_d(n / base, base);
		return (count + ft_print_d(n % base, base));
	}
}
