/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update_physics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:05:29 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/09 15:20:46 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/time.h>
#include <unistd.h>

void	game_update_physics(t_game *game)
{
	if (game->physics)
	{
		game->pos.z += game->mz;
		game->mz -= PH_GRAVITY;
		if ((game->pos.z <= 0 && map_get(&game->map, game->pos.x,
					game->pos.y) == '0') || (game->pos.z <= 1
				&& map_get(&game->map, game->pos.x, game->pos.y) == '1'))
		{
			game->pos.z = (map_get(&game->map, game->pos.x,
						game->pos.y) == '1');
			game->mz = 0;
		}
	}
	if (game->health <= HEALTH_REGEN_LIMIT)
		game->health += HEALTH_REGEN_RATE;
}

void	game_obj_takedamage(t_obj *o, int dmg)
{
	o->u_obj.enemy.hit_points -= dmg;
	if (o->u_obj.enemy.hit_points <= 0)
		o->type = OBJ_NONE;
}

void	game_update_matrix(t_game *game)
{
	float	f;

	if (game->matrix_mode_mix > 0 && game->ticks % MATTEX_PERIOD == 0)
	{
		mattex_update(&game->mt);
		mattex_draw(&game->mt, game, &game->mattex);
	}
	if (game->physics && game_key_pressed(game, KEY_JUMP)
		&& game->pos.z <= (map_get(&game->map, game->pos.x,
				game->pos.y) == '1'))
	{
		if (game->matrix_mode)
			game->mz = PH_JUMP2;
		else
			game->mz = PH_JUMP;
	}
	f = game->matrix_mode * (1 - game->matrix_mode_mix) + !game->matrix_mode
		* game->matrix_mode_mix;
	game->matrix_mode_mix += f * MATMODE_TOGGLE_SPEED * (-1 + 2
			* game->matrix_mode);
	game->matrix_mode_mix = fclamp(game->matrix_mode_mix, 0, 1);
}

void	game_framectrl(t_game *game, struct timeval *now, struct timeval *then)
{
	int	diff;

	diff = timediff(now, then);
	if (diff > (1000 / FRAMERATE) && game->upscale < MAX_UPSCALE)
	{
		game->upscale++;
	}
	while (diff <= (1000 / MAX_FRAMERATE))
	{
		usleep(100);
		gettimeofday(now, NULL);
		diff = timediff(now, then);
	}
	game->last_draw = *then;
	game->fps = 1000 / diff;
}
