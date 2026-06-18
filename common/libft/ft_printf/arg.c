/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:05:34 by triedel           #+#    #+#             */
/*   Updated: 2023/12/05 13:41:46 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"
#include "arg.h"
#include "putarg.h"

// Parse a format specifier
// returns
//   - char pointer to next pos. if valid arg found
//   - NULL otherwise
const char	*arg_parse(const char *s, t_arg *arg) // TODO handle %%
{
	if (*s++ != '%')
		return (NULL);
	ft_bzero((void *) arg, sizeof(t_arg));
	s = arg_parse_flags(s, arg);
	arg->width = 0;
	s = ft_atoi_parse(s, &(arg->width));
	s = arg_parse_precision(s, arg);
	arg->spec = *s;
	return (++s);
}

const char	*arg_parse_flags(const char *s, t_arg *arg)
{
	if (!s)
		return (NULL);
	while (ft_charinset(*s, "-+ #0"))
	{
		(*s == '-') && (arg->flags |= F_LEFT_JUSTIFY);
		(*s == '+') && (arg->flags |= F_FORCE_SIGN);
		(*s == ' ') && (arg->flags |= F_SPACE);
		(*s == '#') && (arg->flags |= F_PRECEED_HEX);
		(*s == '0') && (arg->flags |= F_ZPAD);
		s++;
	}
	return (s);
}

const char	*arg_parse_precision(const char *s, t_arg *arg)
{
	if (!s)
		return (NULL);
	arg->precision = -1;
	if (*s == '.')
	{
		s++;
		s = ft_atoi_parse(s, &(arg->precision));
		if (arg->precision == -1)
			arg->precision = 0;
	}
	return (s);
}

t_argval	arg_get_value(char spec, va_list vargs)
{
	const char	c = spec;
	t_argval	retval;

	if (c == 'd' || c == 'i')
		retval.di = va_arg(vargs, int);
	else if (c == 's')
		retval.s = va_arg(vargs, char *);
	else if (c == 'c')
		retval.c = va_arg(vargs, int);
	else if (c == 'u' || c == 'x' || c == 'X')
		retval.uxx = va_arg(vargs, unsigned int);
	else if (c == 'p')
		retval.p = va_arg(vargs, void *);
	else
		retval.c = c;
	return (retval);
}
