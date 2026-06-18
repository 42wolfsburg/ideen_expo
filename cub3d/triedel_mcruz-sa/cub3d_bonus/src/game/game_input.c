/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:51:57 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 13:59:28 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include "vector.h"

int	game_mousedown(int key, int x, int y, t_game *game)
{
	(void) x, (void) y;
	if (key == Button1)
	{
		if (game->matrix_mode)
			game_shoot(game);
		else
			game_unsetblock(game);
	}
	else if (key == Button2)
		return (0);
	else if (key == Button3)
		game_setblock(game);
	else if (key == Button4)
	{
		game->fov *= 1.1;
		game_calc_camera_params(game);
	}
	else if (key == Button5)
	{
		game->fov *= .9;
		game_calc_camera_params(game);
	}
	return (0);
}

void	game_keydown_controls(t_game *game, int key)
{
	if (key == KEY_MINIMAP)
		game->show_minimap = !game->show_minimap;
	if (key == KEY_DEBUG)
		game->show_debug = !game->show_debug;
	if (key == KEY_MATRIXMODE)
		game->matrix_mode = !game->matrix_mode;
	if (key == KEY_PAUSE)
		game_pause_toggle(game);
	if (key == KEY_PHYSICS)
		game->physics = !game->physics;
	if (key == XK_1)
		game->textures[TXTBOX].scale += 0.1;
	if (key == XK_2)
		game->textures[TXTBOX].scale -= 0.1;
	if (key == KEY_INTERACT)
		game_interact(game);
	// game->fov = fclamp(game->fov, (float) 5 / 180 * M_PI,
	// 		(float) 170 / 180 * M_PI);
	// game_calc_camera_params(game);
	if (key == KEY_EXIT1 || key == KEY_EXIT2)
		mlx_loop_end(game->disp.mlx);
}

int	game_keydown(int key, t_game *game)
{
	if (game->state == S_INTRO)
		game->state = S_RUNNING;
	game_set_key(game, key, 1);
	game_keydown_controls(game, key);
	return (0);
}

int	game_keyup(int key, t_game *game)
{
	game_set_key(game, key, 0);
	return (0);
}
