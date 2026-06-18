/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:48:26 by triedel           #+#    #+#             */
/*   Updated: 2023/12/11 08:41:08 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft.h"
#include "putarg.h"
#include "put_ptr.h"
#include "put_int.h"
#include "put_misc.h"

int	arg_put(t_arg *arg, t_putfunc pf, void *putargs)
{
	const t_putarg_func	putarg_func = putarg_pick_func(arg);
	size_t				written;
	size_t				len;
	char				filler;

	written = 0;
	filler = ' ';
	if (!(arg->flags & F_LEFT_JUSTIFY))
	{
		if (arg->precision == -1 && (arg->flags & F_ZPAD))
		{
			filler = '0';
			written += putsign(arg, pf, putargs) + put0x(arg, pf, putargs);
			len = written + putarg_func(arg, putdummy, NULL);
		}
		else
			len = written + apply_precision(arg, putdummy, NULL, putarg_func) + \
					put0x(arg, putdummy, NULL);
		written += putfill(filler, arg->width - len, pf, putargs);
	}
	(filler != '0') && (written += put0x(arg, pf, putargs));
	written += apply_precision(arg, pf, putargs, putarg_func);
	if (arg->flags & F_LEFT_JUSTIFY)
		written += putfill(filler, arg->width - written, pf, putargs);
	return (written);
}

// Takes care of precision for diuxX
int	apply_precision(t_arg *arg, t_putfunc putfunc, void *putargs,
		t_putarg_func putargfunc)
{
	int	len;
	int	signlen;

	len = 0;
	signlen = 0;
	if (!ft_charinset(arg->spec, "diuxX"))
		return (putargfunc(arg, putfunc, putargs));
	if (!((!(arg->flags & F_LEFT_JUSTIFY)) && \
			(arg->precision == -1 && (arg->flags & F_ZPAD))))
		signlen = putsign(arg, putfunc, putargs);
	if (arg->precision == -1 || \
			(ft_charinset(arg->spec, "di") && \
			arg->value.di == 0 && arg->precision == 0) || \
			(ft_charinset(arg->spec, "uxX") && \
			(arg->value.uxx == 0 && arg->precision == 0)))
		return (signlen + putargfunc(arg, putfunc, putargs));
	len = putargfunc(arg, putdummy, NULL);
	len = putfill('0', arg->precision - len, putfunc, putargs);
	len += putargfunc(arg, putfunc, putargs);
	return (len + signlen);
}

int	putfill(char c, int count, t_putfunc putfunc, void *putargs)
{
	int	i;

	if (count <= 0)
		return (0);
	i = 0;
	while (i++ < count)
		putfunc(c, putargs);
	return (count);
}

t_putarg_func	putarg_pick_func(t_arg *arg)
{
	const char		s = arg->spec;
	t_putarg_func	f;

	f = NULL;
	(s == 'd' || s == 'i') && (f = putarg_int);
	(s == 's') && (f = putarg_str);
	(s == 'c') && (f = putarg_char);
	(s == 'x') && (f = putarg_hex);
	(s == 'X') && (f = putarg_hex_upper);
	(s == 'p') && (f = putarg_ptr);
	(s == 'u') && (f = putarg_uint);
	if (!f)
		f = putarg_char;
	return (f);
}
