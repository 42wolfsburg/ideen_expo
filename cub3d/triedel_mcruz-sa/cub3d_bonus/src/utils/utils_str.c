/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:31:18 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 15:31:21 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// Returns `true` if string `s` ends with string `needle`
bool	ft_endswith(const char *s, const char *needle)
{
	const size_t	len = ft_strlen(s);
	const size_t	nlen = ft_strlen(needle);
	const char		*cur;

	if (nlen > len)
		return (false);
	cur = s + len - nlen;
	return (ft_strcmp(cur, needle) == 0);
}
