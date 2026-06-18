/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:07:52 by jastomme          #+#    #+#             */
/*   Updated: 2024/06/26 13:27:02 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char			*memdest;
	const char		*memsrc;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	memsrc = (const char *)src;
	memdest = (char *)dest;
	if (dest <= src)
		ft_memcpy(memdest, memsrc, len);
	else if (dest > src)
	{
		i = len;
		while (i > 0)
		{
			i--;
			memdest[i] = memsrc[i];
		}
	}
	return (dest);
}
