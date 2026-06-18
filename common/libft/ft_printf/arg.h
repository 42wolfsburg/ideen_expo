/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:05:25 by triedel           #+#    #+#             */
/*   Updated: 2023/12/05 13:18:41 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stdarg.h>

typedef union u_argval
{
	char			*s;
	int				c;
	int				di;
	unsigned int	uxx;
	void			*p;
}	t_argval;

// for original it's		[flags][width][.precision][length]specifier
// we don't need length		[flags][width][.precision]specifier
typedef struct s_arg
{
	unsigned char	flags;
	int				width;
	int				precision;
	char			spec;
	t_argval		value;
}	t_arg;

enum e_flags
{
	F_LEFT_JUSTIFY = 1 << 0,	// -
	F_FORCE_SIGN = 1 << 1,		// +
	F_SPACE = 1 << 2,			// \s
	F_PRECEED_HEX = 1 << 3,		// #
	F_ZPAD = 1 << 4,			// 0
};

/* $$proto_start$$ */

/*  */
/* arg.c */
const char	*arg_parse(const char *s, t_arg *arg);
const char	*arg_parse_flags(const char *s, t_arg *arg);
const char	*arg_parse_precision(const char *s, t_arg *arg);
t_argval	arg_get_value(char spec, va_list vargs);

/* $$proto_end$$ */