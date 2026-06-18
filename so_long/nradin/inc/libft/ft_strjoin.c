/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:23:20 by nradin            #+#    #+#             */
/*   Updated: 2022/11/06 17:17:22 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s1 + j))
	{
		*(s3 + i) = *(s1 + j);
		i++;
		j++;
	}
	j = 0;
	while (*(s2 + j))
	{
		*(s3 + i) = *(s2 + j);
		i++;
		j++;
	}
	*(s3 + i) = 0;
	return (s3);
}
