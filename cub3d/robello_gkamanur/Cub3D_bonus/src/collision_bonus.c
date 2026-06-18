/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:58:41 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 19:59:59 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	check_door_collision(t_door *door, double x, double y)
{
	double	thresh;
	double	center_x;
	double	center_y;

	if (door->is_secret == SECRET_DOOR_YES && door->revealed == 0)
		return (1);
	thresh = 0.5 - (door->door_progress * 0.4);
	center_x = door->door_x + 0.5;
	center_y = door->door_y + 0.5;
	if (fabs(x - center_x) < thresh && fabs(y - center_y) < thresh)
		return (1);
	return (0);
}

int	collision_point(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;
	int	i;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map.height)
		return (1);
	if (map_x < 0 || map_x >= game->map.width)
		return (1);
	if (game->map.map[map_y][map_x] == WALL)
		return (1);
	i = 0;
	while (i < game->doors.count)
	{
		if (game->doors.list[i].door_x == map_x
			&& game->doors.list[i].door_y == map_y)
			return (check_door_collision(&game->doors.list[i], x, y));
		i = i + 1;
	}
	return (0);
}

int	ft_check_collision(t_game *game, double new_x, double new_y)
{
	double	radius;
	int		can_move_x;
	int		can_move_y;

	radius = PLAYER_HIT_RADIUS;
	can_move_x = 1;
	can_move_y = 1;
	if (collision_point(game, new_x + radius, game->player.play_y)
		|| collision_point(game, new_x - radius, game->player.play_y))
		can_move_x = 0;
	if (collision_point(game, game->player.play_x, new_y + radius)
		|| collision_point(game, game->player.play_x, new_y - radius))
		can_move_y = 0;
	if (can_move_x == 0 && can_move_y == 0)
	{
		if (!collision_point(game, new_x + radius, game->player.play_y)
			&& !collision_point(game, new_x - radius, game->player.play_y))
			can_move_x = 1;
		if (!collision_point(game, game->player.play_x, new_y + radius)
			&& !collision_point(game, game->player.play_x, new_y - radius))
			can_move_y = 1;
	}
	return ((can_move_x << 1) | can_move_y);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.playdir_x;
	game->player.playdir_x = game->player.playdir_x
		* cos(-game->player.rota_speed) - game->player.playdir_y
		* sin(-game->player.rota_speed);
	game->player.playdir_y = old_dir_x * sin(-game->player.rota_speed)
		+ game->player.playdir_y * cos(-game->player.rota_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-game->player.rota_speed)
		- game->player.plane_y * sin(-game->player.rota_speed);
	game->player.plane_y = old_plane_x * sin(-game->player.rota_speed)
		+ game->player.plane_y * cos(-game->player.rota_speed);
}

void	handle_movement(t_game *game)
{
	if (game->input.keys & FWRD)
		move_forward(game);
	if (game->input.keys & BWRD)
		move_backward(game);
	if (game->input.keys & LEFT)
		move_left(game);
	if (game->input.keys & RIGHT)
		move_right(game);
	if (game->input.keys & TURN_L)
		rotate_left(game);
	if (game->input.keys & TURN_R)
		rotate_right(game);
}
