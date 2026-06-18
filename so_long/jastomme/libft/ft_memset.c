/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:47:49 by jastomme          #+#    #+#             */
/*   Updated: 2024/06/26 13:15:00 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = (char *)str;
	while (i < len)
	{
		mem[i] = c;
		i++;
	}
	return (str);
}

/* - memset fills the first 'len' bytes of the memory pointed by 'str' 
with the constant byte 'c'.
returns a pointer to the memory area 'str';
- we type cast 'str' to 'char *' to handle the memory block byte by byte 
bc char takes 1 byte only
- we itterate trough the pointer(i++) and fill every byte with the value of 'c'.
- the function returns the original pointer 'str'.(start of memory block).*/