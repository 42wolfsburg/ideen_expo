/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:25 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 15:46:07 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	*ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*z;

	z = s;
	count = 0;
	while (count < n)
	{
		*z = '\0';
		z++;
		count++;
	}
	return (z);
}
