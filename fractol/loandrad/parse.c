/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2026/06/18 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static double	parse_fraction(char *str, int *i)
{
	double	fraction;
	double	scale;

	fraction = 0;
	scale = 0.1;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			fraction += (str[*i] - '0') * scale;
			scale *= 0.1;
			(*i)++;
		}
	}
	return (fraction);
}

double	ft_atof(char *str)
{
	int		i;
	int		sign;
	double	number;

	i = 0;
	sign = 1;
	number = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		number = number * 10 + str[i++] - '0';
	number += parse_fraction(str, &i);
	return (number * sign);
}
