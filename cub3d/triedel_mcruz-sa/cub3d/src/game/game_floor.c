/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:44:57 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 14:46:06 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_color	game_render_ceil(t_game *game, int bufpos, t_pt campos,
		float fstop_diag)
{
	float		dist;
	t_vec		offset;
	t_pt		hitpos;
	t_color		col;
	double		ign;

	col = CTRANSPARENT;
	dist = fabs(fstop_diag / (campos.y + game->cam_height
				* tan(game->rotx))) * (game->pos.z + CAM_HEIGHT - 1);
	offset = vec_scale(vec_normalize(game->hit_buffer[bufpos].ray.dir),
			dist);
	hitpos = vec_add(offset, vec_from_vec3(&game->pos));
	if (map_get(&game->map, hitpos.x, hitpos.y) == '1')
	{
		if (FLOOR_TEXTURE)
		{
			col = img_getpxlr(&game->textures[TXTFLOOR],
					modf(hitpos.x, &ign), modf(hitpos.y, &ign));
			col = col_lum(col, 0.8);
		}
		else
			col = game->map.floor;
	}
	return (col);
}

t_color	game_render_floor_ceil(t_game *game, int bufpos, float z,
		t_vec diag_camy)
{
	t_color		col;
	float		dist;
	t_vec		offset;
	t_pt		hitpos;
	double		i;

	col = game->map.ceiling;
	if (z < 0)
	{
		col = game->map.floor;
		if (FLOOR_TEXTURE)
		{
			dist = fabs(diag_camy.x / (diag_camy.y + game->cam_height
						* tan(game->rotx))) * (CAM_HEIGHT + game->pos.z);
			offset = vec_scale(vec_normalize(game->hit_buffer[bufpos].ray.dir),
					dist);
			hitpos = vec_add(offset, vec_from_vec3(&game->pos));
			if (map_get(&game->map, hitpos.x, hitpos.y))
				col = col_fade(img_getpxlr(&game->textures[TXTFLOOR],
							modf(hitpos.x, &i), modf(hitpos.y, &i)), dist);
		}
	}
	return (col);
}
