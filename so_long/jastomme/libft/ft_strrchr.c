/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:58:17 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:10 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(s);
	if (str[i] == (char)c)
		return (str + i);
	while (i > 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	if (str[0] == (char)c)
		return (str);
	return (NULL);
}

/*int	main(void)
{
	ft_printf("%p\n", ft_strrchr("Hello World", 'o'));
	ft_printf("%p\n", strrchr("Hello World", 'o'));
}*/
