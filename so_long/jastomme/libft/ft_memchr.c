/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:57:12 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*memsrc;
	size_t	i;

	memsrc = (char *)s;
	i = 0;
	while (i < n)
	{
		if (memsrc[i] == (char)c)
			return (memsrc + i);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	ft_printf("%p\n", ft_memchr("Hello World", '\0', 12));
	ft_printf("%p\n", memchr("Hello World", '\0', 12));
}*/
