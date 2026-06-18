/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:24:19 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 22:33:21 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "arg.h"
#include "putfuncs.h"

/* $$proto_start$$ */

/*  */
/* put_ptr.c */
int		putarg_ptr(t_arg *arg, t_putfunc putfunc, void *putargs);
int		putptr(uintptr_t val, bool uppercase, t_putfunc putfunc, void *putargs);
char	hexdigit(char digit, const bool uppercase);
int		put0x(t_arg *arg, t_putfunc putfunc, void *putargs);

/* $$proto_end$$ */
