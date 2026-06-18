/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_object_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:02 by triedel           #+#    #+#             */
/*   Updated: 2024/08/09 17:12:34 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_color	obj_get_pixel_door(t_game *game, t_hitrec *hit, float *z, int *past)
{
	t_color	col;

	if (*z < hit->obj->pos.z || *z > hit->obj->pos.z + hit->obj->height)
		return (CTRANSPARENT);
	else if (past)
		*past = 1 - 2 * (*z < hit->obj->pos.z);
	col = img_getpxlr(&game->textures[TXTDOOR], hit->r / hit->obj->width + .5
			- hit->obj->u_obj.door.open / 100.0, (1 - ((*z - hit->obj->pos.z)
					/ hit->obj->height)));
	return (col);
}

t_color	obj_get_pixel_agent(t_game *game, t_hitrec *hit, float *z, int *past)
{
	t_color	col;
	t_img	*i;

	col = CTRANSPARENT;
	if (*z < hit->obj->pos.z && past)
		*past = -1;
	else if (past && *z > hit->obj->pos.z + hit->obj->height)
		*past = 1;
	else
	{
		i = obj_get_agent_texture(game);
		col = img_getpxlr(i, -hit->r / hit->obj->width + .5, (1 - *z
					/ hit->obj->height));
	}
	return (col);
}

t_img	*obj_get_agent_texture(t_game *game)
{
	const int	d = 15;
	int			t;

	t = game->ticks;
	if (game->matrix_mode)
	{
		if (t / d % 4 == 0)
			return (&game->textures[TXTAGENT0]);
		else if (t / d % 4 == 1)
			return (&game->textures[TXTAGENT1]);
		else if (t / d % 4 == 2)
			return (&game->textures[TXTAGENT2]);
		else if (t / d % 4 == 3)
			return (&game->textures[TXTAGENT1]);
	}
	return (&game->textures[TXTAGENT1]);
}

t_color	obj_get_pixel_pill(t_game *game, t_hitrec *hit, float *z)
{
	t_color	col;

	if (*z < hit->obj->pos.z || *z > hit->obj->pos.z + hit->obj->height)
	{
		return (CTRANSPARENT);
	}
	col = img_getpxlr(&game->textures[TXTPILL], hit->r / hit->obj->width + .5,
			(1 - *z / hit->obj->height));
	return (col);
}

t_color	obj_get_pixel_phonebox(t_game *game, t_hitrec *hit, float *z)
{
	t_color	col;
	float	dist;

	if (*z < hit->obj->pos.z || *z > hit->obj->pos.z + hit->obj->height)
		return (CTRANSPARENT);
	dist = pt3_dist(&hit->obj->pos, &game->pos);
	col = img_getpxlr(&game->textures[TXTPHONEBOX0 + (dist < 3)], -hit->r
			/ hit->obj->width + .5, (1 - *z / hit->obj->height));
	if ((0xffffff & col) == 0x000000)
		col = CTRANSPARENT;
	return (col);
}
