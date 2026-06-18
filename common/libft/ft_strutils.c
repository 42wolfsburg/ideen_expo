/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:45:39 by triedel           #+#    #+#             */
/*   Updated: 2024/01/05 11:51:12 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	ft_endswith(const char *s, const char *end)
{
	int	len;
	int	endlen;

	len = ft_strlen(s);
	endlen = ft_strlen(end);
	if (endlen > len)
		return (false);
	return (ft_strcmp(s + len - endlen, end) == 0);
}
