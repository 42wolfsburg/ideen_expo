/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:11:34 by triedel           #+#    #+#             */
/*   Updated: 2023/11/13 11:33:49 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		size;

	size = ft_strlen(src) + 1;
	dup = malloc(size * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, size);
	return (dup);
}
