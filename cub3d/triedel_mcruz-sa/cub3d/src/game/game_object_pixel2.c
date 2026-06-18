/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_pixel2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:02 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 12:36:12 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/*
	`past` will be set to
	-1 if hit is before object
	0 if hit
	1 if hit is after object
*/
t_color	obj_get_pixel(t_game *game, t_hitrec *hit, float z, int *past)
{
	t_color	col;

	col = CTRANSPARENT;
	if (hit->obj == GRID_WALL)
		col = wall_get_pixel(game, hit, z, past);
	else if (hit->obj->type == OBJ_DOOR)
		col = obj_get_pixel_door(game, hit, &z, past);
	else if (hit->obj->type == OBJ_AGENT)
		col = obj_get_pixel_agent(game, hit, &z, past);
	else if (hit->obj->type == OBJ_PILL)
		col = obj_get_pixel_pill(game, hit, &z);
	else if (hit->obj->type == OBJ_PHONEBOX)
		col = obj_get_pixel_phonebox(game, hit, &z);
	else if (hit->obj->type == OBJ_PLANE)
		col = obj_get_pixel_plane(game, hit, &z, past);
	else if (hit->obj->type == OBJ_BULLET)
		col = obj_get_pixel_bullet(game, hit, &z);
	col = col_fade(col, hit->dist);
	return (col);
}

t_color	obj_get_pixel_plane(t_game *game, t_hitrec *hit, float *z, int *past)
{
	t_color	col;
	t_color	matcol;

	if (*z < hit->obj->pos.z || *z > hit->obj->pos.z + hit->obj->height)
		return (CTRANSPARENT);
	else if (past)
		*past = 1 - 2 * (*z < hit->obj->pos.z);
	col = img_getpxlr(&game->textures[TXTMAX + 1 + hit->obj->texture_id], hit->r
			/ hit->obj->width + .5, (1 - ((*z - hit->obj->pos.z)
					/ hit->obj->height)));
	if (game->matrix_mode_mix > 0.01)
	{
		matcol = img_getpxlr(&game->mattex, hit->r / hit->obj->width + .5, (1
					- ((*z - hit->obj->pos.z) / hit->obj->height)));
		col = col_mix(col, matcol, 1 - (game->matrix_mode_mix
					* MATMODE_MAXMIX));
	}
	return (col);
}

t_color	obj_get_pixel_bullet(t_game *game, t_hitrec *hit, float *z)
{
	t_color	col;

	if (*z < hit->obj->pos.z - hit->obj->height / 2 || *z > hit->obj->pos.z
		+ hit->obj->height / 2)
	{
		return (CTRANSPARENT);
	}
	col = img_getpxlr(&game->textures[TXTBULLET], -hit->r / hit->obj->width
			+ .5, (1 - (.5 + (*z - hit->obj->pos.z) / hit->obj->height)));
	return (col);
}
