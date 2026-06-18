/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:06:38 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 19:08:15 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	fill_coll_enemy_cell(t_game *game, int x, int y, int indices[2])
{
	if (game->map.map[y][x] == COLL)
	{
		game->colls.list[indices[0]].col_x = x + 0.5;
		game->colls.list[indices[0]].col_y = y + 0.5;
		game->colls.list[indices[0]].collected = 0;
		game->colls.list[indices[0]].current_frame = 0;
		indices[0] = indices[0] + 1;
	}
	else if (game->map.map[y][x] == ENEMY)
	{
		game->enemies.list[indices[1]].ene_x = x + 0.5;
		game->enemies.list[indices[1]].ene_y = y + 0.5;
		game->enemies.list[indices[1]].spawn_x = x + 0.5;
		game->enemies.list[indices[1]].spawn_y = y + 0.5;
		game->enemies.list[indices[1]].alive = 1;
		game->enemies.list[indices[1]].current_frame = 0;
		game->enemies.list[indices[1]].ene_speed = ENEMY_SPEED;
		indices[1] = indices[1] + 1;
	}
}

void	fill_door_cell(t_game *game, int x, int y, int *door_idx)
{
	game->doors.list[*door_idx].door_x = x;
	game->doors.list[*door_idx].door_y = y;
	game->doors.list[*door_idx].state = CLOSED;
	game->doors.list[*door_idx].door_progress = 0.0;
	if (game->map.map[y][x] == SECRET)
	{
		game->doors.list[*door_idx].is_secret = SECRET_DOOR_YES;
		game->doors.list[*door_idx].revealed = 0;
	}
	else
	{
		game->doors.list[*door_idx].is_secret = SECRET_DOOR_NO;
		game->doors.list[*door_idx].revealed = 1;
	}
	game->doors.list[*door_idx].last_opened = 0.0;
	*door_idx = *door_idx + 1;
}

void	fill_bonus_entities(t_game *game)
{
	int	x;
	int	y;
	int	indices[3];

	indices[0] = 0;
	indices[1] = 0;
	indices[2] = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.map[y][x] == DOOR || game->map.map[y][x] == SECRET)
				fill_door_cell(game, x, y, &indices[0]);
			else if (game->map.map[y][x] == COLL || game->map.map[y][x]
				== ENEMY)
				fill_coll_enemy_cell(game, x, y, &indices[1]);
			x = x + 1;
		}
		y = y + 1;
	}
}

void	allocate_sprite_list(t_game *game)
{
	int	max_sprites;

	if (game->sprites.list != NULL)
		return ;
	max_sprites = game->colls.total + game->enemies.ene_count;
	if (max_sprites > 0)
	{
		game->sprites.list = malloc(sizeof(t_sprite) * max_sprites);
		if (!game->sprites.list)
		{
			printf("Error: Failed to allocate sprite list\n");
			exit(1);
		}
		printf("  ✓ Allocated sprite list for %d sprites\n", max_sprites);
		game->sprites.count = 0;
	}
	else
		printf("Warning: No sprites to allocate\n");
}

int	allocate_bonus_entities(t_game *game)
{
	if (game->doors.count > 0)
	{
		game->doors.list = malloc(sizeof(t_door) * game->doors.count);
		if (!game->doors.list)
			return (0);
		ft_bzero(game->doors.list, sizeof(t_door) * game->doors.count);
	}
	if (game->colls.total > 0)
	{
		game->colls.list = malloc(sizeof(t_coll) * game->colls.total);
		if (!game->colls.list)
			return (0);
		ft_bzero(game->colls.list, sizeof(t_coll) * game->colls.total);
	}
	if (game->enemies.ene_count > 0)
	{
		game->enemies.list = malloc(sizeof(t_enemy) * game->enemies.ene_count);
		if (!game->enemies.list)
			return (0);
		ft_bzero(game->enemies.list, sizeof(t_enemy) * game->enemies.ene_count);
	}
	return (1);
}
