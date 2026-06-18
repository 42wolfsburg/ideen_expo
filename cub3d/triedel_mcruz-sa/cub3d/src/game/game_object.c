/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:02 by triedel           #+#    #+#             */
/*   Updated: 2024/08/09 17:14:49 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// Add game object `obj` to `game`, in the first
/// free spot of its game object list
void	game_obj_add(t_game *game, t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < MAX_OBJECTS)
	{
		if (game->objects[i].type == OBJ_NONE)
		{
			game->objects[i] = *obj;
			break ;
		}
	}
}

/// Calculate texture coordinates from world coordinates and wall direction
t_pt	mapwall_get_coord(int dir, t_pt3 *wcoord)
{
	double		i;
	const float	x = modf(wcoord->x, &i);
	const float	y = modf(wcoord->y, &i);

	if (dir == DWEST)
		return (vec(y, 1 - wcoord->z));
	else if (dir == DEAST)
		return (vec(1 - y, 1 - wcoord->z));
	else if (dir == DSOUTH)
		return (vec(x, 1 - wcoord->z));
	else if (dir == DNORTH)
		return (vec(1 - x, 1 - wcoord->z));
	return (vec(.5, .5));
}

/// Given a `ray` finds intersections with game object `obj`
t_hitrec	game_obj_intersect(t_game *game, t_obj *obj, const t_line *ray)
{
	t_line		orth;
	t_hitrec	a;

	if (obj->type == OBJ_NONE)
		return (hitnone());
	orth.dir = vec_rotate(vec(1, 0), -game->rot);
	if (obj->type == OBJ_PLANE || obj->type == OBJ_PILL
		|| obj->type == OBJ_DOOR)
		orth.dir = vec_rotate(obj->normal, M_PI / 2);
	orth.loc = vec_from_vec3(&obj->pos);
	a = line_inters_line(ray, &orth);
	if (a.dist > 0 && a.r >= -obj->width / 2 && a.r <= obj->width / 2)
	{
		a.obj = obj;
		return (a);
	}
	return (hitnone());
}

t_color	wall_get_pixel(t_game *game, t_hitrec *hit, float z, int *past)
{
	t_color	matcol;
	int		dir;
	t_pt3	coord;
	t_pt	txtpos;
	t_color	col;

	if (z >= 0 && z <= 1)
	{
		dir = vec_direction(&hit->normal);
		coord = vec3_from_vec(&hit->hit);
		coord.z = z;
		txtpos = mapwall_get_coord(vec_direction(&hit->normal), &coord);
		col = img_getpxlr(&game->textures[dir], txtpos.x, txtpos.y);
		if (game->matrix_mode_mix > 0.01)
		{
			matcol = img_getpxlr(&game->mattex, txtpos.x, txtpos.y);
			col = col_mix(col, matcol, 1 - (game->matrix_mode_mix
						* MATMODE_MAXMIX));
		}
		return (col);
	}
	else if (past)
		*past = 1 - 2 * (z < 0);
	return (CTRANSPARENT);
}
