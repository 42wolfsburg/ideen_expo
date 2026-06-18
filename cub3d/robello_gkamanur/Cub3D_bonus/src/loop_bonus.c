/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:52:00 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 19:52:10 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	ft_castrays(game);
	render_sprites(game);
	if (game->flash > 0)
		draw_flash_overlay(game);
	if (game->bonus.s_minimap.enabled)
		render_minimap(game);
	if (game->gmover.state != GAME_RUNNING)
		render_game_over(game);
	mlx_put_image_to_window(game->mlx, game->window, game->frame.img.img, 0, 0);
}

double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	check_entity_collisions(t_game *game)
{
	check_collectible_collisions(game);
	check_enemy_collisions(game);
}

void	ft_update_running_game(t_game *game, double delta_time)
{
	update_doors(game, delta_time);
	update_enemy_positions(game);
	update_enemy_animation(game);
	update_collectible_frames(game);
	check_entity_collisions(game);
	ft_check_victory(game);
	if (game->flash > 0)
		game->flash--;
	handle_movement(game);
}

int	game_loop(t_game *game)
{
	static double	last_time = 0;
	double			current_time;
	double			delta_time;

	if (last_time == 0)
		last_time = get_current_time();
	current_time = get_current_time();
	delta_time = current_time - last_time;
	last_time = current_time;
	if (delta_time > 0.1)
		delta_time = 0.1;
	if (game->gmover.state == GAME_RUNNING)
		ft_update_running_game(game, delta_time);
	else
	{
		if (game->gmover.fading < 100)
			game->gmover.fading = game->gmover.fading + 2;
	}
	ft_render_frame(game);
	return (0);
}
