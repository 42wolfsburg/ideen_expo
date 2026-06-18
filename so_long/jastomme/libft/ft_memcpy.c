/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:10:31 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	char		*memdest;
	const char	*memsrc;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	memdest = (char *)dest;
	memsrc = (const char *)src;
	i = 0;
	while (i < len)
	{
		memdest[i] = memsrc[i];
		i++;
	}
	return (dest);
}

/*int main()
{
	char src[] = "Hello";
	char dest [10];
	ft_memcpy(dest, src, 4);
	ft_printf("%s\n", dest);
	memcpy(dest, src, 4);
	ft_printf("%s\n", dest);
}*/