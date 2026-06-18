/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:12:49 by jastomme          #+#    #+#             */
/*   Updated: 2024/06/26 12:53:31 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	char	*ptr;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	if (nmemb * size > 2147483647)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

//allocates memory for an array of nmemb elements of size bytes 
//each and returns a pointer to the allocated memory.
//the memory is set to 0
//if nmemb == 0 || size == 0 return (NULL)
//(or a unique ptr value that can be passed to free)
//if nememb * size == int overflow return(NULL)