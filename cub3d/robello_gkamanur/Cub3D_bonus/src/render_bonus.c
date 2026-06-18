/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:16:40 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:36:52 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	prepare_collectibles(t_game *game)
{
	int	idx;

	game->sprites.count = 0;
	idx = 0;
	while (idx < game->colls.total)
	{
		if (game->colls.list[idx].collected == 0)
		{
			game->sprites.list[game->sprites.count].sprite_x
				= game->colls.list[idx].col_x;
			game->sprites.list[game->sprites.count].sprite_y
				= game->colls.list[idx].col_y;
			game->sprites.list[game->sprites.count].type = SPRITE_COLL;
			game->sprites.list[game->sprites.count].tex_id
				= COLL_0 + game->colls.list[idx].current_frame;
			game->sprites.count = game->sprites.count + 1;
		}
		idx = idx + 1;
	}
}

void	prepare_enemies(t_game *game)
{
	int	idx;

	idx = 0;
	while (idx < game->enemies.ene_count)
	{
		if (game->enemies.list[idx].alive != 0)
		{
			game->sprites.list[game->sprites.count].sprite_x
				= game->enemies.list[idx].ene_x;
			game->sprites.list[game->sprites.count].sprite_y
				= game->enemies.list[idx].ene_y;
			game->sprites.list[game->sprites.count].type = SPRITE_ENE;
			game->sprites.list[game->sprites.count].tex_id
				= ENEMY_0 + game->enemies.list[idx].current_frame;
			game->sprites.count = game->sprites.count + 1;
		}
		idx = idx + 1;
	}
}

void	calculate_sprite_distances(t_game *game)
{
	int		idx;
	double	dx;
	double	dy;

	idx = 0;
	while (idx < game->sprites.count)
	{
		dx = game->player.play_x - game->sprites.list[idx].sprite_x;
		dy = game->player.play_y - game->sprites.list[idx].sprite_y;
		game->sprites.list[idx].dist = (dx * dx) + (dy * dy);
		idx = idx + 1;
	}
}

void	render_single_sprite(t_game *game, t_sprite *sprite)
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;

	sprite_x = sprite->sprite_x - game->player.play_x;
	sprite_y = sprite->sprite_y - game->player.play_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.playdir_y
			- game->player.playdir_x * game->player.plane_y);
	transform_x = inv_det * (game->player.playdir_y * sprite_x
			- game->player.playdir_x * sprite_y);
	transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
	if (transform_y > 0)
		draw_sprite_column(game, sprite, transform_x, transform_y);
}

void	render_sprites(t_game *game)
{
	int	idx;

	if (!game->sprites.list)
	{
		printf("ERROR: No sprite list allocated!\n");
		return ;
	}
	prepare_collectibles(game);
	prepare_enemies(game);
	if (game->sprites.count == 0)
	{
		printf("No sprites to render (all collected?)\n");
		return ;
	}
	calculate_sprite_distances(game);
	sort_sprites(game);
	idx = 0;
	while (idx < game->sprites.count)
	{
		render_single_sprite(game, &game->sprites.list[idx]);
		idx = idx + 1;
	}
}
