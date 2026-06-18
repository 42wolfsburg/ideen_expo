/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:50:53 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:52:57 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_collectible(t_game *game, int center_x, int center_y, int radius)
{
	int	delta_x;
	int	delta_y;

	delta_y = -radius;
	while (delta_y <= radius)
	{
		delta_x = -radius;
		while (delta_x <= radius)
		{
			if (delta_x * delta_x + delta_y * delta_y <= radius * radius)
				ft_put_pixel(&game->frame.img, center_x + delta_x,
					center_y + delta_y, 0xFF0000);
			delta_x++;
		}
		delta_y++;
	}
}

void	draw_wall_cell(t_game *game, int start_x, int start_y, int scale)
{
	int	x;
	int	y;

	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			if (x == 0 || y == 0 || x == scale - 1 || y == scale - 1)
				ft_put_pixel(&game->frame.img, start_x + x, start_y + y,
					0x999623);
			else
				ft_put_pixel(&game->frame.img, start_x + x, start_y + y,
					0x222222);
			x++;
		}
		y++;
	}
}

void	draw_floor_cell(t_game *game, int start_x, int start_y, int scale)
{
	int	x;
	int	y;

	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			ft_put_pixel(&game->frame.img, start_x + x, start_y + y, 0x606060);
			x++;
		}
		y++;
	}
}

void	draw_cell(t_game *game, int map_x, int map_y)
{
	int	scale;
	int	start_x;
	int	start_y;

	scale = game->bonus.s_minimap.scale;
	start_x = game->bonus.s_minimap.offset_x + map_x * scale;
	start_y = game->bonus.s_minimap.offset_y + map_y * scale;
	if (game->map.map[map_y][map_x] == '1')
		draw_wall_cell(game, start_x, start_y, scale);
	if (game->map.map[map_y][map_x] == 'C' &&
		!is_collected(game, map_x, map_y))
		draw_collectible(game, start_x + scale / 2,
			start_y + scale / 2, scale / 3);
	if (game->map.map[map_y][map_x] == '0'
			|| game->map.map[map_y][map_x] == '.')
		draw_floor_cell(game, start_x, start_y, scale);
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	map_width_pixels;
	int	map_height_pixels;

	map_width_pixels = game->map.width * game->bonus.s_minimap.scale + 30;
	map_height_pixels = game->map.height * game->bonus.s_minimap.scale + 30;
	y = 0;
	while (y < map_height_pixels)
	{
		x = 0;
		while (x < map_width_pixels)
		{
			ft_put_pixel(&game->frame.img,
				game->bonus.s_minimap.offset_x + x - 15,
				game->bonus.s_minimap.offset_y + y - 15,
				0x222222);
			x++;
		}
		y++;
	}
}
