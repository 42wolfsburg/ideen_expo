/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:28:54 by nradin            #+#    #+#             */
/*   Updated: 2022/12/17 12:14:06 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	parse_conversions(char *s, va_list ap)
{
	if (*s == 'c')
		return (ft_putchar_fd(va_arg(ap, int), 1));
	if (*s == 'd' || *s == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), 1));
	if (*s == 'u')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789"));
	if (*s == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (ft_putnbr_base(va_arg(ap, size_t), "0123456789abcdef") + 2);
	}
	if (*s == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	if (*s == 'x')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (*s == 'X')
		return (ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (*s == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		n;
	va_list	ap;

	va_start(ap, format);
	i = 0;
	n = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			n += parse_conversions((char *)format + i + 1, ap) - 2;
			i += 2;
			continue ;
		}
		write(1, format + i, 1);
		i++;
	}
	va_end(ap);
	return (n + i);
}
