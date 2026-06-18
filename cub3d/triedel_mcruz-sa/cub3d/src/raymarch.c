/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:55:56 by triedel           #+#    #+#             */
/*   Updated: 2024/08/12 16:57:25 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

bool	raymarch_horizontal(t_map *map, t_line *l, t_raymarch *rm)
{
	char	from;
	char	to;

	rm->dx = ft_ternary_int(l->dir.x < 0, -1, 1);
	from = map_get(map, (int)rm->pvert.x - (l->dir.x < 0) - rm->dx,
			(int)rm->pvert.y);
	to = map_get(map, (int)rm->pvert.x - (l->dir.x < 0), (int)rm->pvert.y);
	if ((from == '1' && to == '0') || (from == '0' && to == '1'))
	{
		rm->hit.dist = rm->nxt_dist_vert;
		rm->hit.normal = vec(-rm->dx, 0);
		rm->hit.hit = rm->pvert;
		return (true);
	}
	rm->pvert.x += ft_ternary_int(l->dir.x < 0, -1, 1);
	rm->pvert.y += ft_ternary_float(l->dir.y < 0, -rm->stepy, rm->stepy);
	rm->nxt_dist_vert += rm->step_vert;
	return (false);
}

bool	raymarch_vertical(t_map *map, t_line *l, t_raymarch *rm)
{
	char	from;
	char	to;

	rm->dy = ft_ternary_int(l->dir.y < 0, -1, 1);
	from = map_get(map, (int)rm->phor.x, (int)rm->phor.y - \
			(l->dir.y < 0) - rm->dy);
	to = map_get(map, (int)rm->phor.x, (int)rm->phor.y - (l->dir.y < 0));
	if ((from == '1' && to == '0') || (from == '0' && to == '1'))
	{
		rm->hit.dist = rm->nxt_dist_hor;
		rm->hit.normal = vec(0, -rm->dy);
		rm->hit.hit = rm->phor;
		return (true);
	}
	rm->phor.y += ft_ternary_int(l->dir.y < 0, -1, 1);
	rm->phor.x += ft_ternary_float(l->dir.x < 0, -rm->stepx, rm->stepx);
	rm->nxt_dist_hor += rm->step_hor;
	return (false);
}

void	raymarch_init(t_raymarch *rm, t_map *map, t_line *l)
{
	rm->hit.obj = GRID_WALL;
	rm->hit.dist = -1;
	rm->hit.hit = vec(INFINITY, INFINITY);
	rm->hit.normal = vec(0, 0);
	rm->pvert = map_nxt_vert(map, l);
	rm->phor = map_nxt_hor(map, l);
	rm->nxt_dist_vert = pt_dist(&rm->pvert, &l->loc);
	rm->nxt_dist_hor = pt_dist(&rm->phor, &l->loc);
	rm->step_vert = fabs(1 / l->dir.x);
	rm->step_hor = fabs(1 / l->dir.y);
	rm->stepx = 1 / fabs(l->dir.y) * fabs(l->dir.x);
	rm->stepy = 1 / fabs(l->dir.x) * fabs(l->dir.y);
}

/// Find point where line `l` hits vertical line of `map`
t_pt	map_nxt_vert(t_map *map, t_line *l)
{
	t_pt	res;
	float	distx;

	if (l->dir.x == 0)
		return ((t_pt){INFINITY, INFINITY});
	(void)map;
	res.x = (int)l->loc.x;
	if (l->dir.x > 0)
		res.x += 1.0;
	distx = res.x - l->loc.x;
	res.y = l->loc.y + l->dir.y / l->dir.x * distx;
	return (res);
}

// Find point where line `l` hits horizontal line of map `map`
t_pt	map_nxt_hor(t_map *map, t_line *l)
{
	t_pt	res;
	float	disty;

	if (l->dir.y == 0)
		return ((t_pt){INFINITY, INFINITY});
	(void)map;
	res.y = (int)l->loc.y;
	if (l->dir.y > 0)
		res.y += 1.0;
	disty = res.y - l->loc.y;
	res.x = l->loc.x + l->dir.x / l->dir.y * disty;
	return (res);
}
