/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:49:02 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:50:34 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_draw_arrow_tip(t_img *img, int x, int y, int color)
{
	ft_put_pixel(img, x, y, color);
	ft_put_pixel(img, x + 1, y, color);
	ft_put_pixel(img, x - 1, y, color);
	ft_put_pixel(img, x, y + 1, color);
	ft_put_pixel(img, x, y - 1, color);
}

void	ft_draw_arrow_side(t_game *game, int cx, int cy, int side)
{
	int	tx;
	int	ty;
	int	sx;
	int	sy;
	int	step;

	tx = cx + (int)(game->player.playdir_x * 6);
	ty = cy + (int)(game->player.playdir_y * 6);
	sx = cx + (int)(side * game->player.playdir_y * 3);
	sy = cy + (int)(-side * game->player.playdir_x * 3);
	step = 0;
	while (step <= 6)
	{
		ft_put_pixel(&game->frame.img,
			sx + (step * (tx - sx)) / 6,
			sy + (step * (ty - sy)) / 6,
			0xFFFFFF);
		step++;
	}
}

void	draw_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_cell(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	int	cx;
	int	cy;
	int	tx;
	int	ty;

	cx = game->bonus.s_minimap.offset_x
		+ (int)(game->player.play_x * game->bonus.s_minimap.scale);
	cy = game->bonus.s_minimap.offset_y
		+ (int)(game->player.play_y * game->bonus.s_minimap.scale);
	tx = cx + (int)(game->player.playdir_x * 6);
	ty = cy + (int)(game->player.playdir_y * 6);
	ft_draw_arrow_tip(&game->frame.img, tx, ty, 0xFFFFFF);
	ft_draw_arrow_side(game, cx, cy, -1);
	ft_draw_arrow_side(game, cx, cy, 1);
}

void	render_minimap(t_game *game)
{
	draw_minimap(game);
	draw_walls(game);
	draw_player(game);
}
