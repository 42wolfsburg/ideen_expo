/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:51 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 09:58:12 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	set_bit(unsigned char *c, unsigned int i, int val)
{
	if (val == 1)
		*c |= (1 << i);
	else if (val == 0)
		*c &= ~(1 << i);
}

bool	get_bit(unsigned char c, unsigned int i)
{
	return (1 & (c >> i));
}
