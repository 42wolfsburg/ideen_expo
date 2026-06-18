/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:00:33 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 12:34:32 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_model	*model_new(size_t nverts, size_t nedges)
{
	t_model	*mod;

	mod = malloc(sizeof(t_model));
	if (!mod)
		return (NULL);
	mod->name = NULL;
	mod->nverts = nverts;
	mod->nedges = nedges;
	mod->verts = malloc(sizeof(t_cvec) * nverts);
	if (!mod->verts)
		return (free(mod), NULL);
	mod->edges = malloc(sizeof(t_edge) * nedges);
	if (!mod->edges)
		return (free(mod), free(mod->verts), NULL);
	return (mod);
}

void	model_bounding_box(t_model *mod, t_vec *min, t_vec *max)
{
	unsigned int	i;

	if (!mod || mod->nverts == 0 || mod->nedges == 0)
	{
		*min = vec(-1, -1, -1);
		*max = vec(1, 1, 1);
	}
	*min = vec_from_cvec(mod->verts[0]);
	*max = vec_from_cvec(mod->verts[0]);
	i = 0;
	while (i < mod->nverts)
		cvec_setminmax(&mod->verts[i++], min, max);
}

void	model_normalize(t_model *mod)
{
	unsigned int	i;
	t_vec			min;
	t_vec			max;
	t_vec			center;
	float			scale;

	if (!mod || mod->nverts == 0 || mod->nedges == 0)
		return ;
	model_bounding_box(mod, &min, &max);
	center.x = (max.x + min.x) / 2;
	center.y = (max.y + min.y) / 2;
	center.z = (max.z + min.z) / 2;
	scale = 2.0 / ft_max_float(max.z - min.z, \
			ft_max_float(max.x - min.x, max.y - min.y));
	i = 0;
	while (i < mod->nverts)
	{
		mod->verts[i].x = scale * (mod->verts[i].x - center.x);
		mod->verts[i].y = scale * (mod->verts[i].y - center.y);
		mod->verts[i].z = scale * (mod->verts[i].z - center.z);
		i++;
	}
}

void	model_del(void *arg)
{
	t_model	*mod;

	mod = (t_model *) arg;
	if (mod->name)
		free(mod->name);
	free(mod->verts);
	free(mod->edges);
	free(mod);
}

void	*model_del_null(void *arg)
{
	model_del(arg);
	return (NULL);
}

// void	model_colorize(t_model *mod)
// {
// 	t_vec			min;
// 	t_vec			max;
// 	float			extent_z;
// 	unsigned int	i;

// 	model_bounding_box(mod, &min, &max);
// 	extent_z = max.z - min.z;
// 	i = 0;
// 	while (i < mod->nverts)
// 	{
// 		mod->verts[i].col = 0x0000ffff * (mod->verts[i].z - min.z) / extent_z;
// 		i++;
// 	}
// }

// void	model_fdf_vert(t_model *mod, t_fdf fdf)
// {

// }

// void	model_fdf_horiz(t_model *mod, t_fdf fdf)
// {
// }

// void	model_vdel(void *arg)
// {
// 	model_del((t_model *) arg);
// }

// void	model_translate(t_model *mod, t_cvec v)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (i < mod->nverts)
// 	{
// 		mod->verts[i] = cvec_translate(mod->verts[i], v);
// 		i++;
// 	}
// }