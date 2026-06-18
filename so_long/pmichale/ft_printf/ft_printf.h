/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:35:17 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 15:59:00 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef unsigned long long	t_xd;

int		ft_printf(const char *format, ...);
int		ft_printfsub(va_list *lst, char func);
int		ft_putnbr_hex(unsigned long long numbr, char *base);
char	*ft_itoa_u_s(unsigned long long num, char *str);
char	*ft_itoa_s(long long num, char *str);
void	ft_bzero(void *string, size_t ncount);
void	*ft_memset(void *bmemory, int valu, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
