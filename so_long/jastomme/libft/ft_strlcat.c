/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:36:01 by jastomme          #+#    #+#             */
/*   Updated: 2024/06/26 10:03:02 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	remaining;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	remaining = 0;
	if (size <= dstlen)
		return (size + srclen);
	remaining = size - dstlen - 1;
	ft_strlcpy(dst + dstlen, src, remaining + 1);
	return (dstlen + srclen);
}
