/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:57:31 by jastomme          #+#    #+#             */
/*   Updated: 2024/10/03 15:47:18 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(const char *specifier, int i, va_list ap)
{
	int	count;

	count = 0;
	if (specifier[i] == 'c')
		count = count + ft_print_c((char)va_arg(ap, int));
	else if (specifier[i] == 's')
		count = count + ft_print_s(va_arg(ap, char *));
	else if (specifier[i] == 'p')
		count = count + ft_print_p(va_arg(ap, void *));
	else if (specifier[i] == 'd')
		count = count + ft_print_d(va_arg(ap, int), 10);
	else if (specifier[i] == 'i')
		count = count + ft_print_d(va_arg(ap, int), 10);
	else if (specifier[i] == 'u')
		count = count + ft_print_d(va_arg(ap, unsigned int), 10);
	else if (specifier[i] == 'x')
		count = count + ft_print_d(va_arg(ap, unsigned int), 16);
	else if (specifier[i] == 'X')
		count = count + ft_print_d_upper(va_arg(ap, unsigned int), 16);
	else if (specifier[i] == '%')
		count = count + ft_print_c('%');
	else
		count = count + ft_print_c('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		length;
	va_list	ap;

	i = 0;
	length = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
				break ;
			length = length + print_format(format, i, ap);
		}
		else
			length = length + ft_print_c(format[i]);
		i++;
	}
	va_end(ap);
	return (length);
}
