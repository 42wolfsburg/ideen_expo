/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:05:29 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/13 14:06:30 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/time.h>
#include <unistd.h>

void	game_update_phonebox(t_game *game, int *i)
{
	char	*cpy;

	if (game_collides_obj(game, &game->objects[*i]))
	{
		cpy = ft_strdup(game->map.level);
		map_deinit(&game->map);
		game_deinit_textures(game);
		game_init_map(game, cpy);
		free(cpy);
	}
}

void	game_update_pill(t_game *game, t_pt objpos, t_pt pos, int *i)
{
	game->objects[*i].normal = vec_rotate(game->objects[*i].normal, .05);
	objpos = vec_from_vec3(&game->objects[*i].pos);
	if (pt_dist(&objpos, &pos) < .25)
	{
		game->matrix_mode = 1;
		game->objects[*i].type = OBJ_NONE;
	}
}

void	game_update_bullet(t_game *game, int *i)
{
	int			j;
	t_line		ray;
	t_hitrec	h;

	j = -1;
	while (++j < MAX_OBJECTS)
	{
		if (game->objects[j].type != OBJ_AGENT)
			continue ;
		ray.loc = vec_from_vec3(&game->objects[*i].pos);
		ray.dir = vec_from_vec3(&game->objects[*i].u_obj.bullet.speed);
		h = game_obj_intersect(game, &game->objects[j], &ray);
		if (isfinite(h.dist)
			&& h.dist <= vec_len(vec_from_vec3 \
				(&game->objects[*i].u_obj.bullet.speed)))
		{
			game_obj_takedamage(&game->objects[j], 20);
			game->objects[*i].type = OBJ_NONE;
		}
	}
	game->objects[*i].pos.x += game->objects[*i].u_obj.bullet.speed.x;
	game->objects[*i].pos.y += game->objects[*i].u_obj.bullet.speed.y;
	game->objects[*i].pos.z += game->objects[*i].u_obj.bullet.speed.z;
}

void	game_update_matrix_agent(t_game *game, t_pt objpos, t_pt pos, int *i)
{
	float	d;
	t_vec	diff;

	d = pt_dist(&objpos, &pos);
	if (d >= AGENT_ATTACK_RANGE)
	{
		diff.x = objpos.x - pos.x;
		diff.y = objpos.y - pos.y;
		diff = vec_normalize(diff);
		game->objects[*i].pos.x += -diff.x * AGENT_SPD;
		game->objects[*i].pos.y += -diff.y * AGENT_SPD;
	}
	else
	{
		game->health -= AGENT_ATTACK_DMG;
		game->damage_taken = 1;
		if (game->health <= 0)
			game->state = S_OVER;
	}
}

void	game_update_door_object(t_game *game, int *i)
{
	t_obj	*o;
	t_door	*d;

	o = &game->objects[*i];
	d = &o->u_obj.door;
	if (d->state == D_OPENING)
	{
		d->open += DOOR_OPENSPEED;
		if (d->open >= DOOR_MAXOPEN)
			d->state = D_OPEN;
	}
	else if (d->state == D_CLOSING)
	{
		d->open -= DOOR_CLOSESPEED;
		if (d->open <= 0)
			d->state = D_CLOSED;
	}
}
