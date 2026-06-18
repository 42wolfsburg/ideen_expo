/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guruvenu <guruvenu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:43:47 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 19:21:19 by guruvenu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// size_t	ft_strlen(const char *str);
// int		ft_strncmp(char *s1, char *s2, size_t n);

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	len_small;
	char	*ptr_b;
	char	*ptr_s;

	len_small = ft_strlen(small);
	ptr_b = (char *)big;
	ptr_s = (char *)small;
	if (*small == '\0')
		return ((char *)ptr_b);
	i = 0;
	while ((*ptr_b != '\0') && (len_small + i <= len))
	{
		if (ft_strncmp(ptr_b, ptr_s, len_small) == 0)
			return ((char *)ptr_b);
		ptr_b++;
		i++;
	}
	return (NULL);
}
