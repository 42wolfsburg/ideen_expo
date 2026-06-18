/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:59:47 by aputiev           #+#    #+#             */
/*   Updated: 2023/01/04 16:00:31 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_ident_process(char specifier, va_list symbols)
{	
	int	char_printed;

	char_printed = 0;
	if (specifier == 'c')
		char_printed += ft_putchar(va_arg(symbols, int));
	if (specifier == '%')
		char_printed += ft_putchar('%');
	else if (specifier == 'd' || specifier == 'i')
		char_printed += ft_putnbr(va_arg(symbols, int));
	else if (specifier == 's')
		char_printed += ft_putstr(va_arg(symbols, char *));
	else if (specifier == 'u')
		char_printed += ft_put_unsigned_nbr(va_arg(symbols, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		char_printed += ft_put_hex(va_arg(symbols, int), specifier);
	else if (specifier == 'p')
		char_printed += ft_pointer(va_arg(symbols, unsigned long long));
	return (char_printed);
}

int	ft_printf(const char *specifier, ...)
{	
	int		char_printed;
	int		i;
	va_list	symbols;

	va_start(symbols, specifier);
	i = 0;
	char_printed = 0;
	while (specifier[i])
	{	
		if (specifier[i] == '%')
		{	
			char_printed += ft_ident_process(specifier[i + 1], symbols);
			i++;
		}
		else
		{
			char_printed += ft_putchar(specifier[i]);
		}
		i++;
	}
	va_end (symbols);
	return (char_printed);
}

// #include <stdio.h>

// int main ()
// {
// // /*test 1 - char */
// ft_printf("%c", '0');
// printf("\n");
// printf("%c", '0');
// printf("\n");
//
// // /*test 2 - % */
// ft_printf("value is %%");
// printf("\n");
// printf("value is %%");
// printf("\n");
//
// // /*test 3 - int d */
// ft_printf(" %d ", 1);
// printf("\n");
// printf(" %d ", 1);
// printf("\n");
//
// // /*test 4 - int i */
// ft_printf("value is %i", 1525);
// printf("\n");
// printf("value is %i", 1525);
// printf("\n");
//
// /*test 5 - string  */
// ft_printf(" %s ", "-");
// printf("\n");
// printf(" %s ", "-");
// printf("\n");
//
// // /*test 6 - unsigned int */
// ft_printf("value is %u", 1911);
// printf("\n");
// printf("value is %u", 1911);
// printf("\n");
//
/*test 7 - hex lower case */
// ft_printf(" %x ", LONG_MIN);
// printf("\n");
// printf(" %lx ", LONG_MIN);
// printf("\n");
//
/*test 8 - pointer adress */
//   	int a = 1;
// 	int *ptr;
//     ptr  = &a;
// 
// ft_printf("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
// printf("\n");
// printf("%pp%p%p", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
// printf("\n");

// return 0;

// }