/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:45:37 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/07 21:27:14 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	sub_decimal(va_list *lst)
{
	char		wrt[13];
	long long	i;
	long long	j;

	j = va_arg(*lst, int);
	ft_itoa_s((unsigned long long)j, wrt);
	i = 0;
	while (wrt[i] != '\0')
	{
		if (write(1, &wrt[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

static int	sub_hexa(va_list *lst, char *hex)
{
	return (ft_putnbr_hex(va_arg(*lst, unsigned int), hex));
}

static int	sub_type(va_list *lst, char chr)
{
	if (chr == 'c')
		return (ft_printfsub(lst, 'c'));
	else if (chr == 's')
		return (ft_printfsub(lst, 's'));
	else if (chr == 'p')
		return (ft_printfsub(lst, 'p'));
	else if (chr == 'd')
		return (sub_decimal(lst));
	else if (chr == 'i')
		return (sub_decimal(lst));
	else if (chr == 'u')
		return (ft_printfsub(lst, 'u'));
	else if (chr == 'x')
		return (sub_hexa(lst, "0123456789abcdef"));
	else if (chr == 'X')
		return (sub_hexa(lst, "0123456789ABCDEF"));
	else if (chr == '%')
		return (write(1, "%%", 1));
	else
		return (0);
}

int	sub_splitmain(va_list *lst, int i, int count, const char *format)
{
	int	store;

	store = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			store = sub_type(lst, format[i]);
			if (store == -1)
				return (-1);
			count = count + store;
		}
		else
		{
			if (write(1, &format[i], 1) <= 0)
				return (-1);
			count++;
		}
	}
	return (count);
}

/// @brief one printy boy
/// @param format
/// @return 
int	ft_printf(const char *format, ...)
{
	va_list	lst;
	int		i;
	int		count;

	va_start(lst, format);
	i = -1;
	count = 0;
	count = sub_splitmain(&lst, i, count, format);
	va_end(lst);
	return (count);
}

// int	main()
// {
// 	int	i;
// 	int	j;

// 	i = ft_printf("%d \n %% %s", -200 "lmao");
// 	j = printf("%d \n", -200);
// 	printf(" ft=%i og=%i\n", i, j);
// 	// i = ft_printf(" %p %p \n", -2147483648, 2147483647);
// 	// j = printf(" %p %p \n", -2147483648, 2147483647);
// 	// ft_printf(" ft=%i og=%i\n", i, j);
// 	// i = ft_printf(" %p %p \n", -9223372036854775808, 9223372036854775807);
// 	// j = printf(" %p %p \n", -9223372036854775808, 9223372036854775807);
// 	// ft_printf(" ft=%i og=%i\n", i, j);
// 	// return (0);
// }

// gcc -fsanitize=address -g ft_printf.c libft/libft.a
// ./a.out | cat -e
