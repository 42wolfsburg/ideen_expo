/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfextra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:05:02 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 15:57:57 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	sub_nowwriteit(char *str, int i)
{
	while (i >= 0)
	{
		if (write(1, &str[i], 1) < 0)
			return (-1);
		i--;
	}
	return (1);
}

/// @brief writes a number from decimal into hex (unsigned)
/// @param numbr decimal number
/// @param base expected length of 16 characters total
/// @return returns the amount of characters this function wrote
int	ft_putnbr_hex(unsigned long long numbr, char *base)
{
	int		i;
	char	str[32];

	if (numbr == 0)
	{
		if (write(1, &base[0], 1) < 0)
			return (-1);
		return (1);
	}
	i = 0;
	ft_bzero(str, 32);
	while (numbr != 0)
	{
		str[i] = base[numbr % 16];
		numbr = numbr / 16;
		i++;
	}
	if (sub_nowwriteit(str, i - 1) < 0)
		return (-1);
	return (i);
}

static char	*sub_edgecase(int num, char *str)
{
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	return (0);
}

static char	*sub_cr(t_xd num, t_xd len, t_xd minus, char *str)
{
	int	i;

	i = 0;
	while (i != 13)
	{
		str[i] = '\0';
		i++;
	}
	if (minus == 0)
		len = len - 1;
	while (num)
	{
		str[len] = num % 10 + '0';
		num = num / 10;
		len--;
	}
	if (minus == 1)
		str[len] = '-';
	return (str);
}

/// @brief turns an unsigned integer into a string
/// @param num the int given (long long!!!!! LOOOLL)
/// @return returns the *char
char	*ft_itoa_u_s(unsigned long long num, char *str)
{
	t_xd	numcpy;
	t_xd	len;
	t_xd	minus;

	len = 0;
	if (num == 0)
		return (sub_edgecase(num, str));
	minus = 0;
	if (num < 0)
	{
		minus = 1;
		num = num * -1;
	}
	numcpy = num;
	while (numcpy)
	{
		numcpy = numcpy / 10;
		len++;
	}
	return (sub_cr(num, len, minus, str));
}
