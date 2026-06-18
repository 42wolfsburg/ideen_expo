/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:29:26 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 22:33:40 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "putfuncs.h"
#include "arg.h"

/* $$proto_start$$ */

/*  */
/* put_int.c */
int	putuint(unsigned int i, t_putfunc putfunc, void *putargs);
int	putsign(t_arg *arg, t_putfunc putfunc, void *putargs);
int	putarg_int(t_arg *arg, t_putfunc putfunc, void *putargs);
int	putarg_uint(t_arg *arg, t_putfunc putfunc, void *putargs);
int	putarg_char(t_arg *arg, t_putfunc putfunc, void *putargs);

/* $$proto_end$$ */