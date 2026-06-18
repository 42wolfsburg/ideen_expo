/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ft_atof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:19 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/07 13:02:21 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

double	map_ft_atof(const char *str)
{
	double	number;
	double	fraction;
	int		sign;

	str = map_ft_atof_skip_whitespace(str);
	sign = map_ft_atof_parse_sign(&str);
	number = map_ft_atof_integer_part(&str);
	fraction = map_ft_atof_fractional_part(&str);
	return ((number + fraction) * sign);
}

double	map_ft_atof_fractional_part(const char **str)
{
	double	fraction;
	double	place;

	fraction = 0;
	place = 0.1;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction += (**str - '0') * place;
			place *= 0.1;
			(*str)++;
		}
	}
	return (fraction);
}

double	map_ft_atof_integer_part(const char **str)
{
	double	number;

	number = 0;
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + (**str - '0');
		(*str)++;
	}
	return (number);
}

int	map_ft_atof_parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
	{
		(*str)++;
	}
	return (sign);
}

const char	*map_ft_atof_skip_whitespace(const char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return (str);
}
