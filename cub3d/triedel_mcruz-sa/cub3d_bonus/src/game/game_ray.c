/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:08 by triedel           #+#    #+#             */
/*   Updated: 2024/08/12 16:21:21 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/*
Finds all hits of the `ray` with world.
Returns list of hits sorted by distance
Hits can be both with walls or any other game objects.
In case of a wall hit, a hitrec's obj will be set to NULL;
*/
void	game_get_2d_hits(t_game *game, t_hitrec *hitlist, t_line ray)
{
	const t_line	ray_orig = ray;
	int				i;
	int				j;

	i = -1;
	while (1)
	{
		hitlist[++i] = map_ray_intersect(&game->map, &ray);
		hitlist[i].dist = pt_dist(&ray_orig.loc, &hitlist[i].hit);
		ray.loc = vec_add(hitlist[i].hit, vec_scale(ray.dir, RAY_MARCH_DELTA));
		if (!(isfinite(hitlist[i].dist) && i < MAXHITS))
			break ;
	}
	j = -1;
	while (++j < MAX_OBJECTS)
	{
		if (game->objects[j].type != OBJ_NONE)
		{
			hitlist[i] = game_obj_intersect(game, &game->objects[j], &ray_orig);
			if (isfinite(hitlist[i].dist))
				i++;
		}
	}
	hitlist[i] = hitnone();
	hitlist_sort(hitlist);
}
