/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:02 by jastomme          #+#    #+#             */
/*   Updated: 2024/06/25 11:36:39 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nmbr;
	int		digits[10];
	int		i;

	nmbr = (long)n;
	i = 0;
	if (nmbr < 0)
	{
		write(fd, "-", 1);
		nmbr = nmbr * -1;
	}
	if (nmbr == 0)
		write(fd, "0", 1);
	while (nmbr > 0)
	{
		digits[i] = (nmbr % 10) + 48;
		nmbr = nmbr / 10;
		i++;
	}
	while (i > 0)
	{
		write(fd, &digits[i - 1], 1);
		i--;
	}
}
