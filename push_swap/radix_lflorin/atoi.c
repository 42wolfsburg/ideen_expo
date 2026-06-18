/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:57:22 by lea               #+#    #+#             */
/*   Updated: 2026/05/28 14:33:47 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int ft_isspace(int c)
// {
// 	return((c >= 9 && c <= 13) || c == 32 ? 1:0);
// }

// int ft_isdigit(int c)
// {
// 	return(c>=48 && c <= 57 ? 1:0);
// }

// int ft_atoi(const char *str)
// {
// 	int res;
// 	int i;
// 	int sign;

// 	res = 0;
// 	i = 0;
// 	sign = 1;

// 	while(ft_isspace(str[i]))
// 		i++;
// 	if(str[i] == '-')
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	while(ft_isdigit(str[i]))
// 	{
// 		res *= 10;
// 		res += str[i] -48;
// 		i++;
// 	}
// 	return(res *= sign);
// }

// static int	ft_isspace(int c);

// int ft_atoi(const char *nptr)
// {
//     long number;
//     int sign;
//     int i;

//     number = 0;
//     sign = 1;
//     i = 0;
//     while (ft_isspace(nptr[i]))
//         i++;
//     if (nptr[i] == '+')
//         i++;
//     if (nptr[i] == '-')
//     {
//         sign = -1;
//         i++;
//     }
//     while (nptr[i] >= '0' && nptr[i] <= '9')
//     {
//         number = number * 10 + (nptr[i] - '0');
//         i++;
//     }
//     if (nptr[i] != '\0')
//         return (error());
//     if (number * sign > INT_MAX || number * sign < INT_MIN)
//         return (error());
//     return ((int)(number * sign));
// }

// static int	ft_isspace(int c)
// {
// 	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
// 		return (1);
// 	return (0);
// }

long	ft_atol(char *str)
{
	long	result;
	int		i;
	int		sign;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
