/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_stl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:28:55 by triedel           #+#    #+#             */
/*   Updated: 2024/01/17 19:35:11 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_STL_H
# define LOAD_STL_H

# include "display.h"

// size of triangle in bytes
# define SIZE_TRI	50
// number of triangles to read at once for parsing
# define BUFFER_TRIS	50000 // todo: playing with this makes it crash

/* $$proto_start$$ */

/* load_stl.c */
t_cvec		stl_read_vertex(unsigned char *c);
bool		stl_read_triangle(unsigned char **c, t_model *mod);
bool		stl_read_body(int fd, t_model *mod, size_t size);
t_model		*stl_load(int fd);

/* $$proto_end$$ */

#endif