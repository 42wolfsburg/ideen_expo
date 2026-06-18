/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putfuncs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:46:01 by triedel           #+#    #+#             */
/*   Updated: 2023/12/08 20:46:16 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef void	(*t_putfunc)(char a, void *b);

/* $$proto_start$$ */

/*  */
/* putfuncs.c */
void	putstr(char c, void *s);
void	putstdout(char c, void *_);
void	putdummy(char c, void *_);

/* $$proto_end$$ */