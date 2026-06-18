/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfitoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 21:29:28 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 15:58:06 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

void	*ft_memset(void *bmemory, int valu, size_t len)
{
	size_t			i;
	unsigned char	*mcpy;

	mcpy = (unsigned char *)bmemory;
	i = 0;
	while (i < len)
		mcpy[i++] = (unsigned char)valu;
	return (bmemory);
}

void	ft_bzero(void *string, size_t ncount)
{
	ft_memset(string, 0, ncount);
}

static char	*sub_edgecase(int num, char *str)
{
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (num == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		str[11] = '\0';
		return (str);
	}
	return (0);
}

static char	*sub_createchar(int num, int len, int minus, char *str)
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

/// @brief turns an integer into a string
/// @param num the int given (long long!!!!! LOOOLL)
/// @return returns the *char
char	*ft_itoa_s(long long num, char *str)
{
	long long	numcpy;
	long long	len;
	long long	minus;

	len = 0;
	if (num == 0 || num == -2147483648)
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
	return (sub_createchar(num, len, minus, str));
}
