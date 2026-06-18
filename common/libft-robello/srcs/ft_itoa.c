/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guruvenu <guruvenu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:28:02 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 19:21:19 by guruvenu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		i;

	i = ft_len(n);
	nbr = (char *)malloc((i + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[i--] = 0;
	if (n == 0)
	{
		nbr[0] = '0';
		return (nbr);
	}
	if (n < 0)
		nbr[0] = '-';
	while (n != 0)
	{
		if (nbr[0] == '-')
			nbr[i--] = '0' + -(n % 10);
		else
			nbr[i--] = '0' + (n % 10);
		n = n / 10;
	}
	return (nbr);
}
