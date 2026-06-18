/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_misc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:31:36 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 22:36:46 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "putfuncs.h"
#include "arg.h"

/* $$proto_start$$ */

/*  */
/* put_misc.c */
int	putarg_str(t_arg *arg, t_putfunc putfunc, void *putargs);
int	putarg_hex(t_arg *arg, t_putfunc putfunc, void *putargs);
int	putarg_hex_upper(t_arg *arg, t_putfunc putfunc, void *putargs);

/* $$proto_end$$ */