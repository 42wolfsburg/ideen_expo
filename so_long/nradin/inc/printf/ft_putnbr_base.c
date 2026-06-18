/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:52:16 by nradin            #+#    #+#             */
/*   Updated: 2022/12/17 12:16:28 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 32 || base[i] > 126)
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_putnbr_base(size_t nbr, char *base)
{
	size_t		size;
	size_t		i;
	char		output[65];

	if (!check_base(base))
		return (0);
	i = 0;
	size = ft_strlen(base);
	while (nbr > 0 || i == 0)
	{
		output[i] = base[nbr % size];
		nbr = nbr / size;
		i++;
	}
	size = i;
	while (i-- > 0)
	{
		write(1, &output[i], 1);
	}
	return (size);
}
