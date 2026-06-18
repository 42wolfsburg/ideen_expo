/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:01:32 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*mem1;
	char	*mem2;
	size_t	i;

	mem1 = (char *)s1;
	mem2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (mem1[i] != mem2[i])
			return ((unsigned char)mem1[i] - (unsigned char)mem2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	ft_printf("%d\n", ft_memcmp("Hello World", "llo", 10));
	ft_printf("%d\n", memcmp("Hello World", "llo", 10));
}*/
