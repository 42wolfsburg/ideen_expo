/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:24:09 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 22:38:49 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put_ptr.h"
#include "../libft.h"

int	putarg_ptr(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	int	written;

	if (arg->value.uxx == 0 && arg->precision == 0)
		return (0);
	written = putptr((uintptr_t) arg->value.p, false, putfunc, putargs);
	return (written);
}

int	putptr(uintptr_t val, bool uppercase, t_putfunc putfunc, void *putargs)
{
	int				len;
	int				i;
	bool			started;
	unsigned char	nibble;

	len = 0;
	started = false;
	i = 2 * sizeof(void *);
	while (i-- > 0)
	{
		nibble = (uintptr_t) val >> (i * 4) & 0xf;
		if (nibble || started || i == 0)
		{
			putfunc(hexdigit(nibble, uppercase), putargs);
			started = true;
			len++;
		}
	}
	return (len);
}

char	hexdigit(char digit, const bool uppercase)
{
	const char	start = 'a' - uppercase * ('a' - 'A');

	if (digit < 10)
		return ('0' + digit);
	else if (digit <= 0xf)
		return (start + digit - 10);
	else
		return ('\0');
}

int	put0x(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	char	x;

	if (!ft_charinset(arg->spec, "pxX"))
		return (0);
	if (arg->spec == 'p' || (arg->flags & F_PRECEED_HEX && \
			arg->value.di != 0))
	{
		x = 'x';
		if (arg->spec == 'X')
			x = 'X';
		putfunc('0', putargs);
		putfunc(x, putargs);
		return (2);
	}
	return (0);
}
