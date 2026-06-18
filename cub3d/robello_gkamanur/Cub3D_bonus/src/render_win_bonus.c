/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:33:41 by robello           #+#    #+#             */
/*   Updated: 2026/01/25 18:30:00 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_texture_centered(t_game *game, t_img *tex, float alpha)
{
	int	sx;
	int	sy;
	int	x;
	int	y;
	int	color;

	if (alpha <= 0.0f || !tex || !tex->img)
		return ;
	sx = (game->win_w - tex->width) / 2;
	sy = (game->win_h - tex->height) / 2;
	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			color = *(int *)(tex->addr + (y * tex->linen + x * (tex->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&game->frame.img, sx + x, sy + y,
					blend_color(get_pxl_color(&game->frame.img, sx + x, sy + y),
						color, alpha));
			x = x + 1;
		}
		y = y + 1;
	}
}

void	draw_color_overlay(t_game *game, int color, float alpha)
{
	int	x;
	int	y;
	int	bg;
	int	blended;

	if (alpha <= 0.0f)
		return ;
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			bg = get_pxl_color(&game->frame.img, x, y);
			blended = blend_color(bg, color, alpha);
			my_mlx_pixel_put(&game->frame.img, x, y, blended);
			x = x + 1;
		}
		y = y + 1;
	}
}

void	draw_flash_overlay(t_game *game)
{
	int		x;
	int		y;
	float	alpha;

	alpha = (float)(game->flash * 32) / 255.0f;
	if (alpha > 1.0f)
		alpha = 1.0f;
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			my_mlx_pixel_put(&game->frame.img, x, y,
				blend_color(get_pxl_color(&game->frame.img, x, y), 0xFF5400,
					alpha));
			x = x + 1;
		}
		y = y + 1;
	}
}

void	render_game_over(t_game *game)
{
	t_img	*tex;
	float	progress;
	int		target_color;

	if (game->gmover.state == GAME_RUNNING)
		return ;
	progress = game->gmover.fading / 100.0f;
	if (game->gmover.state == GAME_OVER)
	{
		target_color = 0x8B0000;
		tex = &game->tex.tex[G_OVER];
	}
	else
	{
		target_color = 0xFFD700;
		tex = &game->tex.tex[Y_WIN];
	}
	if (progress <= 0.5f)
		draw_color_overlay(game, target_color, progress * 2.0f);
	else
	{
		draw_color_overlay(game, target_color, 1.0f);
		draw_texture_centered(game, tex, (progress - 0.5f) * 2.0f);
	}
}

void	render_win_fade(t_game *game)
{
	int	color;
	int	y;
	int	x;

	if (game->gmover.state != GAME_WIN)
		return ;
	if (game->gmover.fading < 100)
		game->gmover.fading += 2;
	color = (game->gmover.fading << 24);
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			ft_put_pixel(&game->frame.img, x, y, color);
			x++;
		}
		y++;
	}
}
