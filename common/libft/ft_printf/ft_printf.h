/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:53:55 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 20:53:59 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdarg.h>
#include "putfuncs.h"

/* $$proto_start$$ */

/*  */
/* ft_printf.c */
int	putf(const char *format, va_list vargs, t_putfunc putfunc, void *putargs);
int	ft_vprintf(const char *format, va_list args);
int	ft_vsprintf(char *s, const char *format, va_list args);
int	ft_printf(const char *format, ...);
int	ft_sprintf(char *s, const char *format, ...);

/* $$proto_end$$ */
