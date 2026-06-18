/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:21:09 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 14:33:03 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	game_shoot(t_game *game)
{
	t_obj	bullet;
	t_vec	spd;

	bullet.type = OBJ_BULLET;
	bullet.pos = game->pos;
	bullet.pos.z += CAM_HEIGHT;
	bullet.normal = vec_rotate(vec(0, -1), game->rot);
	bullet.width = .1;
	bullet.height = .1;
	spd = vec_scale(vec_rotate(vec(0, -1), -game->rot), 1);
	bullet.pos.x += spd.x;
	bullet.pos.y += spd.y;
	bullet.u_obj.bullet.speed = vec3_from_vec(&spd);
	bullet.u_obj.bullet.speed.z = tan(game->rotx);
	game_obj_add(game, &bullet);
}

void	game_setblock(t_game *game)
{
	t_line		ray;
	t_hitrec	res;

	ray.dir = vec_rotate(vec(0, -1), -game->rot);
	ray.loc = vec_from_vec3(&game->pos);
	res = map_ray_intersect(&game->map, &ray);
	map_set(&game->map, (int) res.hit.x - (res.normal.x < 0),
		(int) res.hit.y - (res.normal.y < 0), '1');
}

void	game_unsetblock(t_game *game)
{
	t_line		ray;
	t_hitrec	res;

	ray.dir = vec_rotate(vec(0, -1), -game->rot);
	ray.loc = vec(game->pos.x, game->pos.y);
	res = map_ray_intersect(&game->map, &ray);
	map_set(&game->map, (int) res.hit.x - (res.normal.x > 0),
		(int) res.hit.y - (res.normal.y > 0), '0');
}

void	game_interact(t_game *game)
{
	t_line		ray;
	int			i;
	t_hitrec	h;
	t_door		*d;

	ray.dir = vec_rotate(vec(0, -1), -game->rot);
	ray.loc = vec_from_vec3(&game->pos);
	i = -1;
	while (++i < MAX_OBJECTS)
	{
		if (game->objects[i].type == OBJ_NONE)
			continue ;
		h = game_obj_intersect(game, &game->objects[i], &ray);
		if (h.obj && h.obj->type == OBJ_DOOR)
		{
			d = &h.obj->u_obj.door;
			if (d->state == D_CLOSED)
				d->state = D_OPENING;
			if (d->state == D_OPEN)
				d->state = D_CLOSING;
		}
	}
}

void	game_pause_toggle(t_game *game)
{
	if (game->state == S_PAUSED)
	{
		game_mouse_trap(game);
		game->state = S_RUNNING;
	}
	else if (game->state == S_RUNNING)
	{
		game_mouse_release(game);
		game->state = S_PAUSING;
	}
}
