/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:31:24 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 22:38:20 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "put_misc.h"
#include "put_ptr.h"

int	putarg_str(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	const char	nullstr[] = "(null)";
	const char	*s;
	int			i;
	int			len;

	s = arg->value.s;
	if (!s)
		s = nullstr;
	len = ft_strlen(s);
	if (arg->precision != -1 && arg->precision < len)
		len = arg->precision;
	i = 0;
	while (s[i] && i < len)
		putfunc(s[i++], putargs);
	return (len);
}

int	putarg_hex(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	int	written;

	if (arg->value.uxx == 0 && arg->precision == 0)
		return (0);
	written = putptr((uintptr_t) arg->value.uxx, false, putfunc, putargs);
	return (written);
}

int	putarg_hex_upper(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	int	written;

	if (arg->value.uxx == 0 && arg->precision == 0)
		return (0);
	written = putptr((uintptr_t) arg->value.uxx, true, putfunc, putargs);
	return (written);
}
