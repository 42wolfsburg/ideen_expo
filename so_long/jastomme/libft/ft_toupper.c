/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:14:40 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
	{
		c = c - 32;
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

	a = 'a';
	z = 'z';
	x = 'Z';
	ft_printf("%c\n", ft_toupper (a));
	ft_printf("%c\n", ft_toupper (z));
	ft_printf("%c\n", ft_toupper (x));
}*/