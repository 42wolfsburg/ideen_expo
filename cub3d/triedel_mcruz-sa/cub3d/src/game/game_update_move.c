/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:05:29 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/09 15:13:10 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <sys/time.h>
#include <unistd.h>

/// rotate player by `diff` (counter-clockwise)
void	game_rot(t_game *game, float diff)
{
	game->rot += diff;
	if (game->rot < 0)
		game->rot += M_PI * 2;
	if (game->rot >= 2 * M_PI)
		game->rot -= M_PI * 2;
}

// TODO: keep this distance to walls
/*
float diag =
	hypot(hypot(game->cam_width / 2, game->fstop), game->cam_height / 2);
*/
void	game_move(t_game *game, t_vec *dir)
{
	const t_pt	nxtpos = vec_add(vec(game->pos.x, game->pos.y), *dir);
	t_pt		tmp;

	tmp = vec(game->pos.x, nxtpos.y);
	if (!game_collides(game, vec3_from_vec(&tmp)))
		game->pos.y = nxtpos.y;
	tmp = vec(nxtpos.x, game->pos.y);
	if (!game_collides(game, vec3_from_vec(&tmp)))
		game->pos.x = nxtpos.x;
}

void	game_update_walk(t_game *game)
{
	t_vec		walkdir;
	const float	m = 0.12;

	walkdir = vec(0, 0);
	if (game_key_pressed(game, KEY_FORWARD))
		walkdir = vec_add(walkdir, vec(0, -1));
	if (game_key_pressed(game, KEY_BACKWARD))
		walkdir = vec_add(walkdir, vec(0, 1));
	if (game_key_pressed(game, KEY_SLIDELEFT))
		walkdir = vec_add(walkdir, vec(-1, 0));
	if (game_key_pressed(game, KEY_SLIDERIGHT))
		walkdir = vec_add(walkdir, vec(1, 0));
	if (vec_nonzero(&walkdir))
	{
		walkdir = vec_rotate(vec_scale(vec_normalize(walkdir), m), -game->rot);
		game_move(game, &walkdir);
	}
}

void	game_update_move(t_game *game)
{
	game_handle_mouse_input(game);
	if (game_key_pressed(game, KEY_RIGHT))
		game_rot(game, -ROT_SPEED);
	if (game_key_pressed(game, KEY_LEFT))
		game_rot(game, ROT_SPEED);
	if (game_key_pressed(game, KEY_UP))
		game->rotx += ROT_SPEED;
	if (game_key_pressed(game, KEY_DOWN))
		game->rotx -= ROT_SPEED;
	if (!game->physics)
	{
		if (game_key_pressed(game, KEY_MOVEUP) || game_key_pressed(game,
				KEY_MOVEUP2))
			game->pos.z += SPEED_MOVEVERT;
		if (game_key_pressed(game, KEY_MOVEDOWN) || game_key_pressed(game,
				KEY_MOVEDOWN2))
			game->pos.z -= SPEED_MOVEVERT;
	}
}

void	game_handle_mouse_input(t_game *game)
{
	int	x;
	int	y;
	int	xoffset;
	int	yoffset;

	mlx_mouse_get_pos(game->disp.mlx, game->disp.win, &x, &y);
	mlx_mouse_move(game->disp.mlx, game->disp.win, game->disp.width / 2,
		game->disp.height / 2);
	xoffset = game->disp.width / 2 - x;
	yoffset = game->disp.height / 2 - y;
	game_rot(game, (float)xoffset / game->disp.width * M_PI * MOUSE_SENS_Y);
	if (ROTX)
	{
		game->rotx += (float)yoffset / game->disp.height * M_PI * MOUSE_SENS_X;
		game->rotx = fclamp(game->rotx, -M_PI / 4, M_PI / 4);
	}
}
