/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:44:15 by aputiev           #+#    #+#             */
/*   Updated: 2023/01/04 16:02:00 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_lenght(unsigned long long n)
{	
	int	i;

	i = 0;
	while (n != 0)
	{
		n = (n / 16);
		i++;
	}	
	return (i);
}

void	ft_hex_ptr(unsigned long long n)
{
	if (n > 15)
	{
		ft_hex_ptr(n / 16);
		ft_hex_ptr(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar((n + 48));
		else
			ft_putchar(n - 10 + 97);
	}
}

int	ft_pointer(unsigned long long n)
{
	if (n == 0)
	{
		return (write(1, "0x0", 3));
	}
	else
	{	
		write(1, "0x", 2);
		ft_hex_ptr(n);
	}
	return (ft_ptr_lenght(n)+2);
}
