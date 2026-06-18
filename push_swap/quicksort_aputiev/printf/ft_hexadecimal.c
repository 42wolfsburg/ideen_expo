/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:37:43 by aputiev           #+#    #+#             */
/*   Updated: 2022/12/30 17:38:05 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_lenght(unsigned int n)
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

int	ft_put_hex(int m, char specifier)
{
	unsigned int	n;

	n = (unsigned int) m;
	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	else
	{
		if (specifier == 'x')
			ft_hex_lowercase(n);
		if (specifier == 'X')
			ft_hex_uppercase(n);
	}
	return (ft_hex_lenght(n));
}

void	ft_hex_lowercase(unsigned int n)
{	
	if (n > 15)
	{
		ft_hex_lowercase(n / 16);
		ft_hex_lowercase(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar((n + 48));
		else
			ft_putchar((n - 10 + 97));
	}	
}

void	ft_hex_uppercase(unsigned int n)
{	
	if (n > 15)
	{
		ft_hex_uppercase(n / 16);
		ft_hex_uppercase(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar((n + 48));
		else
			ft_putchar(n - 10 + 65);
	}	
}
