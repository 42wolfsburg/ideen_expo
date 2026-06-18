/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guruvenu <guruvenu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:48:11 by gkamanur          #+#    #+#             */
/*   Updated: 2025/12/08 19:21:19 by guruvenu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// size_t	ft_strlen(const char *str);

char	my_fun1(unsigned int i, char c)
{
	if (i % 2 == 0)
		if (c >= 65 && c <= 90)
			return (c + 32);
	if (i % 2 != 0)
		if (c >= 97 && c <= 122)
			return (c - 32);
	return (c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	i = 0;
	while (s[i] != 0)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
