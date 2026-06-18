/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_model.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:20:23 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 15:52:09 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>
#include "load_fdf.h"
#include "load_stl.h"
#include "display.h"

t_model	*model_load(const char *file)
{
	t_model	*mod;
	t_fdf	fdf;
	int		fd;

	fd = 0;
	if (ft_strcmp(file, "-") != 0)
		fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (ft_endswith(file, ".fdf") || ft_endswith(file, ".FDF") || \
			ft_strcmp(file, "-") == 0)
		mod = model_from_fdf(fdf_load(fd, &fdf));
	else if (ft_endswith(file, ".stl") || ft_endswith(file, ".STL"))
		mod = stl_load(fd);
	else
		return (NULL);
	if (fd != 0)
		close(fd);
	if (!mod)
		return (NULL);
	mod->name = ft_strdup(file);
	if (!mod->name)
		return (model_del_null(mod), NULL);
	model_normalize(mod);
	return (mod);
}

void	model_from_fdf_make_edges(t_model *mod, int sizex, int sizey)
{
	int	x;
	int	y;

	y = -1;
	while (++y < sizey)
	{
		x = 0;
		while (++x < sizex)
		{
			mod->edges[mod->nedges].a = sizex * y + x - 1;
			mod->edges[mod->nedges].b = sizex * y + x;
			mod->nedges++;
		}
	}
	x = -1;
	while (++x < sizex)
	{
		y = 0;
		while (++y < sizey)
		{
			mod->edges[mod->nedges].a = sizex * (y - 1) + x;
			mod->edges[mod->nedges].b = sizex * y + x;
			mod->nedges++;
		}
	}
}

void	model_from_fdf_make_verts(t_model *mod, t_fdf fdf, int sizex, int sizey)
{
	int			x;
	int			y;
	float		scale;
	t_fdf_line	line;

	scale = 2.0 / ft_max(sizex, sizey);
	y = 0;
	while (fdf)
	{
		line = *((t_fdf_line *) fdf->content);
		x = -1;
		while (++x < line.len)
		{
			mod->verts[mod->nverts] = cvec(-(scale * sizex / 2) + scale * x, \
					-(scale * sizey / 2) + scale * y, \
					.25 * scale * line.nodes[x].height, line.nodes[x].color);
			mod->nverts++;
		}
		fdf = fdf->next;
		y++;
	}
}

// converts fdf to t_model and in the process frees fdf list
t_model	*model_from_fdf(t_fdf *fdf)
{
	int			sizex;
	int			sizey;
	t_model		*mod;

	if (!fdf)
		return (NULL);
	fdf_getsize(*fdf, &sizex, &sizey);
	mod = model_new(sizex * sizey, (sizex - 1) * sizey + sizex * (sizey - 1));
	mod->nverts = 0;
	mod->nedges = 0;
	if (!mod)
		return (ft_lstclear_null(fdf, fdf_line_del), NULL);
	model_from_fdf_make_verts(mod, *fdf, sizex, sizey);
	model_from_fdf_make_edges(mod, sizex, sizey);
	return (ft_lstclear_null(fdf, fdf_line_del), mod);
}
