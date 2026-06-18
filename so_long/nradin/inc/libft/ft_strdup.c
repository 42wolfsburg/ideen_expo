/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:04:14 by nradin            #+#    #+#             */
/*   Updated: 2022/12/29 11:57:45 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	i;
	char	*d;

	size = ft_strlen(s);
	d = (char *)malloc(size + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(d + i) = *(s + i);
		i++;
	}
	*(d + i) = 0;
	return (d);
}
