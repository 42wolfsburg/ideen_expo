/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:28:26 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 22:32:32 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put_int.h"

int	putuint(unsigned int i, t_putfunc putfunc, void *putargs)
{
	int	written;

	written = 0;
	if (i >= 10)
		written += putuint(i / 10, putfunc, putargs);
	putfunc('0' + i % 10, putargs);
	written++;
	return (written);
}

int	putsign(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	if (!(arg->spec == 'd' || arg->spec == 'i'))
		return (0);
	if (arg->value.di < 0 || arg->flags & F_FORCE_SIGN)
	{
		if (arg->value.di < 0)
			putfunc('-', putargs);
		else
			putfunc('+', putargs);
	}
	else if (arg->flags & F_SPACE)
		putfunc(' ', putargs);
	else
		return (0);
	return (1);
}

int	putarg_int(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	unsigned int	num;

	if (arg->value.di == 0 && arg->precision == 0)
		return (0);
	if (arg->value.di < 0)
		num = -arg->value.di;
	else
		num = arg->value.di;
	return (putuint(num, putfunc, putargs));
}

int	putarg_uint(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	if (arg->value.uxx == 0 && arg->precision == 0)
		return (0);
	return (putuint((unsigned int) arg->value.di, putfunc, putargs));
}

int	putarg_char(t_arg *arg, t_putfunc putfunc, void *putargs)
{
	putfunc(arg->value.c, putargs);
	return (1);
}

// int	putarg_int(t_arg *arg, t_putfunc putfunc, void *putargs)
// {
// 	return (apply_precision(arg, putfunc, putargs, putarg_int_sub));
// }

// int	putarg_uint(t_arg *arg, t_putfunc putfunc, void *putargs)
// {
// 	return (apply_precision(arg, putfunc, putargs, putarg_uint_sub));
// }