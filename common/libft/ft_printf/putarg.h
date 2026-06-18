/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putarg.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:48:12 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 20:48:20 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "putfuncs.h"
#include "arg.h"

typedef int	(*t_putarg_func)(t_arg *arg, t_putfunc putfunc, void *putargs);

/* $$proto_start$$ */

/*  */
/* putarg.c */
int				arg_put(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_str(t_arg *arg, t_putfunc putfunc, void *putargs);
int				apply_precision(t_arg *arg, t_putfunc putfunc, void *putargs,
					t_putarg_func putargfunc);
int				putuint(unsigned int i, t_putfunc putfunc, void *putargs);
int				putsign(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_int(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_int_sub(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_uint(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_uint_sub(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_char(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putfill(char c, int count, t_putfunc putfunc, void *putargs);
int				putarg_hex(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_hex_upper(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putarg_ptr(t_arg *arg, t_putfunc putfunc, void *putargs);
int				putptr(uintptr_t val, bool uppercase, t_putfunc putfunc,
					void *putargs);
char			hexdigit(char digit, const bool uppercase);
int				put0x(t_arg *arg, t_putfunc putfunc, void *putargs);
t_putarg_func	putarg_pick_func(t_arg *arg);

/* $$proto_end$$ */
