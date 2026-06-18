/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:45:43 by triedel           #+#    #+#             */
/*   Updated: 2023/12/11 08:43:15 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "arg.h"
#include "putarg.h"

int	putf(const char *format, va_list vargs, t_putfunc putfunc, void *putargs)
{
	int				len;
	const char		*parse_res;
	t_arg			arg;

	len = 0;
	while (*format)
	{
		if (format[0] == '%' && format[1] == '%')
			format++;
		else if (*format == '%')
		{
			parse_res = arg_parse(format, &arg);
			arg.value = arg_get_value(arg.spec, vargs);
			if (parse_res)
			{
				len += arg_put(&arg, putfunc, putargs);
				format = parse_res;
				continue ;
			}
		}
		putfunc(*format++, putargs);
		len++;
	}
	return (len);
}

int	ft_vprintf(const char *format, va_list args)
{
	int		len;
	int		retval;
	int		writeres;
	char	*s;
	va_list	argcopy;

	va_copy(argcopy, args);
	len = putf(format, args, putdummy, NULL);
	if (len < 0)
		return (-1);
	s = (char *) malloc((len + 1) * sizeof(char));
	if (!s)
		return (-1);
	retval = ft_vsprintf(s, format, argcopy);
	if (retval < 0)
		return (-1);
	writeres = write(STDOUT_FILENO, s, len);
	free(s);
	if (writeres < 0)
		return (-1);
	else
		return (retval);
}

int	ft_vsprintf(char *s, const char *format, va_list args)
{
	char	*c;
	int		retval;

	c = s;
	retval = putf(format, args, putstr, &c);
	putstr('\0', &c);
	return (retval);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		retval;

	va_start(args, format);
	retval = ft_vprintf(format, args);
	va_end(args);
	return (retval);
}

int	ft_sprintf(char *s, const char *format, ...)
{
	va_list	args;
	int		retval;

	va_start(args, format);
	retval = ft_vsprintf(s, format, args);
	va_end(args);
	return (retval);
}
