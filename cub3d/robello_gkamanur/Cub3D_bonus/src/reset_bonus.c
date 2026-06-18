/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:11:41 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:26:18 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_check_victory(t_game *game)
{
	int		map_x;
	int		map_y;
	int		idx;
	t_door	*door;

	map_x = (int)game->player.play_x;
	map_y = (int)game->player.play_y;
	idx = find_door_at_position(game, map_x, map_y);
	if (idx == -1)
		return ;
	door = &game->doors.list[idx];
	if (door->is_secret == SECRET_DOOR_YES && door->state == OPEN)
	{
		game->gmover.state = GAME_WIN;
		game->gmover.fading = 0;
	}
}

void	set_west_direction(t_game *game)
{
	if (game->player.start_char == 'W')
	{
		game->player.playdir_x = -1;
		game->player.playdir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	init_player_direction(t_game *game)
{
	if (game->player.start_char == 'N')
	{
		game->player.playdir_x = 0;
		game->player.playdir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->player.start_char == 'S')
	{
		game->player.playdir_x = 0;
		game->player.playdir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->player.start_char == 'E')
	{
		game->player.playdir_x = 1;
		game->player.playdir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else
		set_west_direction(game);
}

void	ft_reset_game_enemies_and_state(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies.ene_count)
	{
		game->enemies.list[i].alive = 1;
		game->enemies.list[i].current_frame = 0;
		game->enemies.list[i].ene_x = game->enemies.list[i].spawn_x;
		game->enemies.list[i].ene_y = game->enemies.list[i].spawn_y;
		i = i + 1;
	}
	game->gmover.state = GAME_RUNNING;
	game->gmover.fading = 0;
	game->flash = 0;
	game->game_won = 0;
	game->game_time = 0.0;
	game->input.keys = 0;
	printf("\n Get yourself ready to scape alive!!\n");
	ft_display_game_info(game);
}

void	ft_reset_game(t_game *game)
{
	int	i;

	printf("\n\n\n****** GAME RESTARTED ******\n");
	game->player.play_x = game->player.raw_x + 0.5;
	game->player.play_y = game->player.raw_y + 0.5;
	init_player_direction(game);
	i = 0;
	while (i < game->colls.total)
	{
		game->colls.list[i].collected = 0;
		game->colls.list[i].current_frame = 0;
		i = i + 1;
	}
	game->colls.collected = 0;
	i = 0;
	while (i < game->doors.count)
	{
		game->doors.list[i].state = CLOSED;
		game->doors.list[i].door_progress = 0.0;
		game->doors.list[i].last_opened = 0.0;
		if (game->doors.list[i].is_secret == SECRET_DOOR_YES)
			game->doors.list[i].revealed = 0;
		i = i + 1;
	}
	ft_reset_game_enemies_and_state(game);
}
