/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfsub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:06:41 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/07 21:27:44 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	sub_chara(va_list *lst)
{
	char	wrt;

	wrt = va_arg(*lst, int);
	if (write(1, &wrt, 1) >= 0)
		return (1);
	return (-1);
}

static int	sub_string(va_list *lst)
{
	char	*wrt;
	int		i;

	i = -1;
	wrt = va_arg(*lst, char *);
	if (wrt == NULL)
		return (write(1, "(null)", 6));
	while (wrt[++i])
	{
		if (write(1, &wrt[i], 1) < 0)
			return (-1);
	}
	return (i);
}

static int	sub_void(va_list *lst)
{
	long long	i;
	int			ret;

	i = va_arg(*lst, long long);
	if (write(1, "0x", 2) < 0)
		return (-1);
	ret = ft_putnbr_hex(i, "0123456789abcdef");
	if (ret < 0)
		return (-1);
	return (ret + 2);
}

static int	sub_un_decimal(va_list *lst)
{
	char				wrt[13];
	long long			i;
	unsigned long long	j;

	j = va_arg(*lst, unsigned int);
	ft_itoa_u_s((unsigned long long)j, wrt);
	i = 0;
	while (wrt[i] != '\0')
	{
		if (write(1, &wrt[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_printfsub(va_list *lst, char func)
{
	if (func == 'c')
		return (sub_chara(lst));
	if (func == 's')
		return (sub_string(lst));
	if (func == 'p')
		return (sub_void(lst));
	if (func == 'u')
		return (sub_un_decimal(lst));
	else
		return (0);
}
