/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:57:16 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 23:08:21 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_player_near_door(t_game *game, t_door *door)
{
	double	dx;
	double	dy;
	double	distance;

	dx = game->player.play_x - (door->door_x + 0.5);
	dy = game->player.play_y - (door->door_y + 0.5);
	distance = dx * dx + dy * dy;
	return (distance < PLAYER_RANGE * PLAYER_RANGE);
}

void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < game->sprites.count - 1)
	{
		j = i + 1;
		while (j < game->sprites.count)
		{
			if (game->sprites.list[i].dist < game->sprites.list[j].dist)
			{
				temp = game->sprites.list[i];
				game->sprites.list[i] = game->sprites.list[j];
				game->sprites.list[j] = temp;
			}
			j = j + 1;
		}
		i = i + 1;
	}
}

int	create_rgb(int red, int green, int blue)
{
	int	color;

	color = 0;
	color = (red << 16);
	color = color | (green << 8);
	color = color | blue;
	return (color);
}

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width)
		return ;
	if (y < 0 || y >= img->height)
		return ;
	dst = img->addr;
	dst = dst + (y * img->linen);
	dst = dst + (x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;
	int	floor_color;
	int	ceiling_color;

	ceiling_color = create_rgb(game->ceiling_color[0],
			game->ceiling_color[1], game->ceiling_color[2]);
	floor_color = create_rgb(game->floor_color[0],
			game->floor_color[1], game->floor_color[2]);
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		if (y < game->win_h / 2)
			color = ceiling_color;
		else
			color = floor_color;
		while (x < game->win_w)
		{
			ft_put_pixel(&game->frame.img, x, y, color);
			x++;
		}
		y++;
	}
}
