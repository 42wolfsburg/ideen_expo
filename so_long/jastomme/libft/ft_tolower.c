/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:26:59 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
	{
		c = c + 32;
		return (c);
	}
	else
		return (c);
}

/*int	main(void)
{
	int	a;
	int	z;
	int	x;

	a = 'A';
	z = 'B';
	x = 'z';
	ft_printf("%c\n", ft_tolower (a));
	ft_printf("%c\n", ft_tolower (z));
	ft_printf("%c\n", ft_tolower (x));
}*/
