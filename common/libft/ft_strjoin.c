/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:06:20 by triedel           #+#    #+#             */
/*   Updated: 2023/12/01 13:04:37 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	size = len1 + ft_strlen(s2) + 1;
	str = malloc((size) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	ft_strlcpy(str + len1, s2, size);
	return (str);
}
