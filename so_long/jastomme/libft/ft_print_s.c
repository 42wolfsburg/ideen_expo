/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:52:33 by jastomme          #+#    #+#             */
/*   Updated: 2024/09/24 14:07:26 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str == NULL)
		return (ft_print_s("(null)"));
	while (str[i] != '\0')
	{
		ft_print_c(str[i]);
		i++;
		len++;
	}
	return (len);
}
