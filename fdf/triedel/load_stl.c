/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_stl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:19:48 by triedel           #+#    #+#             */
/*   Updated: 2024/01/17 19:35:11 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// \file
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
// #include <endian.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include <libft.h>

#include "load_stl.h"
#include "display.h"

/**
* \page STL
* - \ref stl.c implements a reader for the \
* [STL file format](https://en.wikipedia.org/wiki/STL_(file_format))
* - \ref stl_read can read a \ref t_model from a file descriptor.
*
* Example code
* \code
* #include "stl.h"
* #include "graphics.h"
* t_model m = stl_read(STDIN_FILENO);
*
* // m now allows for direct access to its vertices and edges
* printf("I have %u edges", m.nedges);
* \endcode
*/

/**
* Read an STL vertex
* \param c char pointer to start reading
* \return vertex of type \ref t_cvec
*/
t_cvec	stl_read_vertex(unsigned char *c)
{
	t_cvec	v;

	v.x = *((float *) c);
	c += 4;
	v.y = *((float *) c);
	c += 4;
	v.z = *((float *) c);
	c += 4;
	v.col = C_MODEL;
	return (v);
}

/**
* Read in a triangle section (50 bytes total). Ensure that the segment pointed to
by c is at least 50 bytes.
* 
* \param c		pointer to start of triangle data
* \param i		triangle index counter
* \param mod	model to be filled
* \return `true` on success, `false` on failure
*/
bool	stl_read_triangle(unsigned char **c, t_model *mod)
{
	uint16_t	val;
	t_color		col;

	*c += 12;
	mod->edges[mod->nedges++] = edge(mod->nverts, mod->nverts + 1);
	mod->verts[mod->nverts++] = stl_read_vertex(*c);
	*c += 12;
	mod->edges[mod->nedges++] = edge(mod->nverts, mod->nverts + 1);
	mod->verts[mod->nverts++] = stl_read_vertex(*c);
	*c += 12;
	mod->edges[mod->nedges++] = edge(mod->nverts, mod->nverts - 2);
	mod->verts[mod->nverts++] = stl_read_vertex(*c);
	*c += 12;
	val = *((uint16_t *) c);
	if (val & 1)
	{
		col = cl(((val >> 1) & 0b11111) * 8, \
				((val >> 6) & 0b11111) * 8, \
				((val >> 11) & 0b11111) * 8);
		mod->verts[mod->nverts - 1].col = col;
		mod->verts[mod->nverts - 2].col = col;
		mod->verts[mod->nverts - 3].col = col;
	}
	*c += 2;
	return (true);
}

bool	stl_read_body(int fd, t_model *mod, size_t size)
{
	int				readres;
	unsigned char	buffer[SIZE_TRI * BUFFER_TRIS];
	unsigned char	*c;

	readres = 1;
	while (mod->nverts < size * 3)
	{
		readres = read(fd, buffer, SIZE_TRI * BUFFER_TRIS);
		if (readres <= 0)
			return (false);
		c = buffer;
		while (readres >= SIZE_TRI)
		{
			stl_read_triangle(&c, mod);
			readres -= SIZE_TRI;
		}
		if (readres != 0 || mod->nverts > 3 * size)
			return (false);
	}
	if (mod->nverts == 3 * size && mod->nedges == 3 * size)
		return (true);
	return (false);
}

// /**
// * Parse an STL file and return a \ref s_model "model struct"
// * \return 3D model as \ref t_model
// */
// t_model	*stl_read(int fd)
// {
// 	t_model			*mod;
// 	unsigned char	*c;
// 	unsigned char	buffer[84];
// 	size_t			size;

// 	mod = malloc(sizeof(t_model));
// 	if (!mod)
// 		return (NULL);
// 	if (read(fd, buffer, 84) != 84)
// 		return (NULL);
// 	c = buffer + 80;
// 	size = *((uint32_t *) c);
// 	if (!(0 < size && size < (uint32_t) 10000000))
// 		return (NULL);
// 	mod->verts = ft_calloc(sizeof(t_cvec), 3 * size);
// 	if (!mod->verts)
// 		return (NULL);
// 	mod->edges = ft_calloc(sizeof(t_edge), 3 * size);
// 	if (!mod->edges)
// 		return (NULL);
// 	if (!stl_read_body(fd, &mod, size))
// 	{
// 		free(mod->edges);
// 		free(mod->verts);
// 		return (NULL);
// 	}
// 	return (mod); // todo: where is verts and edges freed?
// }

t_model	*stl_load(int fd)
{
	t_model			*mod;
	unsigned char	*c;
	unsigned char	buffer[84];
	size_t			size;

	if (read(fd, buffer, 84) != 84)
		return (NULL);
	c = buffer + 80;
	size = *((uint32_t *) c);
	mod = model_new(3 * size, 3 * size);
	if (!mod)
		return (NULL);
	mod->nverts = 0;
	mod->nedges = 0;
	if (!(0 < size && size < (uint32_t) 10000000))
		return (model_del_null(mod), NULL);
	if (!stl_read_body(fd, mod, size))
		return (model_del_null(mod), NULL);
	return (mod);
}
