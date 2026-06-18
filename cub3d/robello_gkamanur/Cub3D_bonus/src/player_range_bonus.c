/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:31:09 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:32:11 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_player_in_range(t_game *game, double obj_x, double obj_y, double range)
{
	double	dx;
	double	dy;
	double	dist_sq;
	double	range_sq;

	dx = game->player.play_x - obj_x;
	dy = game->player.play_y - obj_y;
	dist_sq = (dx * dx) + (dy * dy);
	range_sq = range * range;
	if (dist_sq < range_sq)
		return (1);
	return (0);
}

void	check_single_collectible(t_game *game, t_coll *coll)
{
	int	in_range;

	if (coll->collected != 0)
		return ;
	in_range = is_player_in_range(game, coll->col_x, coll->col_y, COLL_RADIUS);
	if (in_range != 0)
	{
		coll->collected = 1;
		game->colls.collected = game->colls.collected + 1;
		game->flash = FLASH_TIME;
		printf("Collected: %d/%d\n", game->colls.collected, game->colls.total);
	}
}

void	check_collectible_collisions(t_game *game)
{
	int	idx;
	int	in_range;

	idx = 0;
	while (idx < game->colls.total)
	{
		if (game->colls.list[idx].collected == 0)
		{
			in_range = is_player_in_range(game, game->colls.list[idx].col_x,
					game->colls.list[idx].col_y, COLL_RADIUS);
			if (in_range != 0)
			{
				game->colls.list[idx].collected = 1;
				game->colls.collected = game->colls.collected + 1;
				game->flash = FLASH_TIME;
				printf("Collected: %d/%d\n", game->colls.collected,
					game->colls.total);
			}
		}
		idx = idx + 1;
	}
}

void	check_single_enemy(t_game *game, t_enemy *ene)
{
	int	in_range;

	if (ene->alive == 0)
		return ;
	if (game->gmover.state != GAME_RUNNING)
		return ;
	in_range = is_player_in_range(game, ene->ene_x, ene->ene_y,
			PLAYER_HIT_RADIUS + 0.5);
	if (in_range != 0)
	{
		game->gmover.state = GAME_OVER;
		game->gmover.fading = 0;
		printf("\n💀 💀  GAME OVER  💀 💀\n");
	}
}

void	check_enemy_collisions(t_game *game)
{
	int	idx;

	idx = 0;
	while (idx < game->enemies.ene_count)
	{
		check_single_enemy(game, &game->enemies.list[idx]);
		idx = idx + 1;
	}
}
