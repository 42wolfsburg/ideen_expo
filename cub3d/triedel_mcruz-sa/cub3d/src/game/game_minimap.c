/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:34:16 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 12:18:47 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_pt	minimap_to_world(t_game *game, t_pt loc)
{
	return (vec_add(vec_from_vec3(&game->pos),
			vec_rotate(vec_scale(loc, MINIMAP_SCALE), -game->rot + M_PI)));
}

float	ipt_dist(t_ipt a, t_ipt b)
{
	return (hypot(a.x - b.x, a.y - b.y));
}

t_color	game_render_minimap_pxl(t_game *game, int x, int y)
{
	const t_pt	ct_offset = vec(game->minimap_center.x - \
			x, game->minimap_center.y - y);
	const t_ipt	pxlhere = ipt(x, y);
	t_pt		here;
	double		a;

	if (ipt_dist(game->minimap_center, pxlhere) < 10)
		return (CGREEN);
	here = minimap_to_world(game, ct_offset);
	if (map_inrange(&game->map, here.x, here.y))
	{
		if (map_get(&game->map, here.x, here.y) == '1')
			return (img_getpxlr(&game->textures[TXTBOX],
					modf(here.x, &a), modf(here.y, &a)));
	}
	return (CTRANSPARENT);
}

void	game_draw_minimap_direction(t_game *game)
{
	t_pt		end;
	int			i;
	t_hitrec	*hit;
	t_line		ray;

	i = -1;
	while (++i < ceil((float)game->disp.width / game->upscale))
	{
		hit = &game->hit_buffer[i].hitlist[0];
		ray = game->hit_buffer[i].ray;
		end = vec_add(
				vec_rotate(vec_scale(ray.dir, 1 / MINIMAP_SCALE * hit->dist),
					game->rot),
				vec(game->minimap_center.x, game->minimap_center.y)
				);
		if (!isfinite(end.x) || !isfinite(end.y))
			continue ;
		img_draw_line(&game->disp.buffer, game->minimap_center,
			ipt(end.x, end.y), CMINIMAPDIR);
	}
}
