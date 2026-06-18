/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:18:50 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 19:21:35 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		move_mask;

	new_x = game->player.play_x + game->player.playdir_x
		* game->player.move_speed;
	new_y = game->player.play_y + game->player.playdir_y
		* game->player.move_speed;
	move_mask = ft_check_collision(game, new_x, new_y);
	if (move_mask & (1 << 1))
		game->player.play_x = new_x;
	if (move_mask & 1)
		game->player.play_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		move_mask;

	new_x = game->player.play_x - game->player.playdir_x
		* game->player.move_speed;
	new_y = game->player.play_y - game->player.playdir_y
		* game->player.move_speed;
	move_mask = ft_check_collision(game, new_x, new_y);
	if (move_mask & (1 << 1))
		game->player.play_x = new_x;
	if (move_mask & 1)
		game->player.play_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	int		move_mask;

	new_x = game->player.play_x + game->player.playdir_y
		* game->player.move_speed;
	new_y = game->player.play_y - game->player.playdir_x
		* game->player.move_speed;
	move_mask = ft_check_collision(game, new_x, new_y);
	if (move_mask & (1 << 1))
		game->player.play_x = new_x;
	if (move_mask & 1)
		game->player.play_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	int		move_mask;

	new_x = game->player.play_x - game->player.playdir_y
		* game->player.move_speed;
	new_y = game->player.play_y + game->player.playdir_x
		* game->player.move_speed;
	move_mask = ft_check_collision(game, new_x, new_y);
	if (move_mask & (1 << 1))
		game->player.play_x = new_x;
	if (move_mask & 1)
		game->player.play_y = new_y;
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.playdir_x;
	game->player.playdir_x = game->player.playdir_x
		* cos(game->player.rota_speed) - game->player.playdir_y
		* sin(game->player.rota_speed);
	game->player.playdir_y = old_dir_x * sin(game->player.rota_speed)
		+ game->player.playdir_y * cos(game->player.rota_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(game->player.rota_speed)
		- game->player.plane_y * sin(game->player.rota_speed);
	game->player.plane_y = old_plane_x * sin(game->player.rota_speed)
		+ game->player.plane_y * cos(game->player.rota_speed);
}
