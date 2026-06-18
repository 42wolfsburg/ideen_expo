/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:08:21 by aputiev           #+#    #+#             */
/*   Updated: 2023/01/04 15:54:58 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_hex_lenght(unsigned int n);
int		ft_put_hex(int m, char specifier);
void	ft_hex_lowercase(unsigned int n);
void	ft_hex_uppercase(unsigned int n);
int		ft_putstr(char *s);
int		ft_num_uns_lenght(unsigned int n);
int		ft_num_lenght(int n);
int		ft_putnbr(int n);
int		ft_put_unsigned_nbr(unsigned int n);
int		ft_ptr_lenght(unsigned long long n);
void	ft_hex_ptr(unsigned long long n);
int		ft_pointer(unsigned long long n);
int		ft_putchar(char c);
int		ft_ident_process(char specifier, va_list symbols);
int		ft_printf(const char *specifier, ...);

#endif
