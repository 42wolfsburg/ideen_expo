/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:59 by nradin            #+#    #+#             */
/*   Updated: 2023/03/02 15:14:54 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	count_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_itoa(int n)
{
	int		i;
	long	n_long;
	int		size;
	char	*res;

	size = count_size(n);
	res = (char *)malloc(size + 1);
	i = size - 1;
	n_long = n;
	if (n_long == 0)
		*res = '0';
	else if (n_long < 0)
	{
		*res = '-';
		n_long = -n_long;
	}
	while (n_long != 0)
	{
		*(res + i) = n_long % 10 + 48;
		n_long /= 10;
		i--;
	}
	*(res + size) = 0;
	return (res);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	*nbr;
	int		size;

	nbr = ft_itoa(n);
	size = ft_strlen(nbr);
	write(fd, nbr, size);
	free(nbr);
	return (size);
}
