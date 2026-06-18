/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:17 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 14:32:42 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/time.h>
#include <unistd.h>

/// Given the viewing plane width and FOV
/// calculates remaining camera parameters
void	game_calc_camera_params(t_game *game)
{
	game->fstop = game->cam_width / (tan(game->fov / 2) * 2);
	game->cam_height = (float)game->disp.height / game->disp.width
		* game->cam_width;
}

void	game_update_objects(t_game *game)
{
	int		i;
	t_pt	objpos;
	t_pt	pos;

	pos = vec_from_vec3(&game->pos);
	i = -1;
	pos = vec(game->pos.x, game->pos.y);
	while (++i < MAX_OBJECTS)
	{
		objpos = vec_from_vec3(&game->objects[i].pos);
		if (game->objects[i].type == OBJ_PHONEBOX)
			game_update_phonebox(game, &i);
		if (game->objects[i].type == OBJ_PILL)
			game_update_pill(game, objpos, pos, &i);
		else if (game->objects[i].type == OBJ_BULLET)
			game_update_bullet(game, &i);
		else if (game->objects[i].type == OBJ_AGENT && game->matrix_mode)
			game_update_matrix_agent(game, objpos, pos, &i);
		else if (game->objects[i].type == OBJ_DOOR)
			game_update_door_object(game, &i);
	}
}

/// Update game logic for next frame
void	game_update(t_game *game)
{
	game_update_physics(game);
	game_update_objects(game);
	game_update_walk(game);
	game_update_move(game);
	game_update_matrix(game);
}

/// Given the x coordinate on the image plane, return the 2D ray for that column
t_line	game_ray_cast(t_game *game, float f)
{
	const float	angle = atan((-(-1 + 2 * f) * game->cam_width / 2) \
				/ game->fstop);
	t_line		ray;
	t_vec		perp;

	ray.dir = vec(-sin(game->rot + angle), -cos(game->rot + angle));
	ray.loc = vec_from_vec3(&game->pos);
	perp = vec_rotate(ray.dir, M_PI / 2);
	ray.loc = vec_add(ray.loc, vec_scale(perp, game->cam_width / 2 * (-1 + 2
					* f)));
	return (ray);
}

int	game_loop(t_game *game)
{
	struct timeval	then;
	struct timeval	now;

	if (game->state == S_PAUSED)
		return (0);
	gettimeofday(&then, NULL);
	if (game->state == S_RUNNING || game->state == S_INTRO)
		game->ticks++;
	game_draw(game);
	if (game->state == S_RUNNING)
		game_update(game);
	if (game->state == S_PAUSING)
		game->state = S_PAUSED;
	gettimeofday(&now, NULL);
	game_framectrl(game, &now, &then);
	return (0);
}
