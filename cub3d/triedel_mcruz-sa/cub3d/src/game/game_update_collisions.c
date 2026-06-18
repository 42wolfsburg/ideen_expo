/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:05:29 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/09 15:09:50 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/time.h>
#include <unistd.h>

bool	game_collides(t_game *game, t_vec3 pos)
{
	const char	next = map_get(&game->map, pos.x, pos.y);

	if (!(game->pos.z >= 1 || !game->physics || (next != '\0' && next != '1')))
		return (true);
	if (pos.x <= 0 || pos.x >= game->map.width || pos.y <= 0
		|| pos.y >= game->map.height)
		return (true);
	return (game_check_object_collisions(game, pos));
}

bool	game_check_object_collisions(t_game *game, t_vec3 pos)
{
	int			i;
	t_line		ray;
	t_hitrec	h1;

	i = -1;
	while (++i < MAX_OBJECTS)
	{
		if (game->objects[i].type == OBJ_NONE)
			continue ;
		ray.loc = vec_from_vec3(&game->pos);
		ray.dir = vec(pos.x - game->pos.x, pos.y - game->pos.y);
		h1 = game_obj_intersect(game, &game->objects[i], &ray);
		if (isfinite(h1.dist) && h1.dist < hypot(pos.x - game->pos.x, pos.y
				- game->pos.y))
		{
			if (game->objects[i].type == OBJ_DOOR
				&& game->objects[i].u_obj.door.state == D_OPEN)
				continue ;
			if (game->pos.z >= game->objects[i].pos.z + game->objects[i].height
				|| game->pos.z + CAM_HEIGHT < game->objects[i].pos.z)
				continue ;
			return (true);
		}
	}
	return (false);
}

bool	game_collides_obj(t_game *game, t_obj *obj)
{
	const t_pt	pos1 = vec_from_vec3(&obj->pos);
	const t_pt	pos2 = vec_from_vec3(&game->pos);
	const float	dist2d = pt_dist(&pos1, &pos2);

	if (obj->type == OBJ_PHONEBOX && dist2d < .25)
	{
		if (game->pos.z >= obj->pos.z + obj->height || game->pos.z
			+ CAM_HEIGHT < obj->pos.z)
			return (false);
		return (true);
	}
	return (false);
}
