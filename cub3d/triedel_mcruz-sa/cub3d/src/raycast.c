/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:53:41 by triedel           #+#    #+#             */
/*   Updated: 2024/08/12 16:58:34 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <math.h>

float	pt_dist(const t_pt *p1, const t_pt *p2)
{
	const float	xdiff = p1->x - p2->x;
	const float	ydiff = p1->y - p2->y;

	return (hypot(xdiff, ydiff));
}

float	pt3_dist(const t_pt3 *p1, const t_pt3 *p2)
{
	const float	xdiff = p1->x - p2->x;
	const float	ydiff = p1->y - p2->y;
	const float	zdiff = p1->z - p2->z;

	return (sqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff));
}

t_vec	vec_swap(t_vec v)
{
	return (vec(v.y, v.x));
}

t_hitrec	line_inters_line(const t_line *l1, const t_line *l2)
{
	const float	den = l1->dir.x * l2->dir.y - l1->dir.y * l2->dir.x;
	const float	numt = (l1->loc.x - l2->loc.x) * -l2->dir.y - \
			(l1->loc.y - l2->loc.y) * -l2->dir.x;
	const float	numu = l1->dir.y * (l1->loc.x - l2->loc.x) - \
			l1->dir.x * (l1->loc.y - l2->loc.y);
	float		t;
	t_hitrec	r;

	if (den == 0)
		return (hitnone());
	t = numt / den;
	if (t < 0)
		return (hitnone());
	r.hit = vec(l1->loc.x + t * l1->dir.x, l1->loc.y + t * l1->dir.y);
	r.r = numu / den;
	r.dist = pt_dist(&l1->loc, &r.hit);
	return (r);
}

/*
	Determine collisions of ray with map using ray marching

	ray marching technique:

	1. figure out where ray first hits vertical and horizontal line
	2. calc. stepx and stepy, the distance traveled to cross one x / one y unit
	3. keep checking map on shortest path intersections
*/

// march on until you we hit a wall
t_hitrec	map_ray_intersect(t_map *map, t_line *l)
{
	t_raymarch	rm;

	raymarch_init(&rm, map, l);
	while (map_inrange(map, rm.pvert.x, rm.pvert.y) || \
			map_inrange(map, rm.phor.x, rm.phor.y))
	{
		if (rm.nxt_dist_vert < rm.nxt_dist_hor)
		{
			if (raymarch_horizontal(map, l, &rm))
				return (rm.hit);
		}
		else
		{
			if (raymarch_vertical(map, l, &rm))
				return (rm.hit);
		}
	}
	return (hitnone());
}
