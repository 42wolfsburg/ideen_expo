/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:06:23 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:12:40 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->linen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	find_door_at_position(t_game *game, int map_x, int map_y)
{
	int	i;

	i = 0;
	while (i < game->doors.count)
	{
		if (game->doors.list[i].door_x == map_x
			&& game->doors.list[i].door_y == map_y)
			return (i);
		i++;
	}
	return (-1);
}

void	check_door_interaction(t_game *game, int dx, int dy)
{
	int	map_x;
	int	map_y;
	int	door_idx;

	map_x = (int)game->player.play_x + dx;
	map_y = (int)game->player.play_y + dy;
	if (map_y < 0 || map_y >= game->map.height)
		return ;
	if (map_x < 0 || map_x >= game->map.width)
		return ;
	door_idx = find_door_at_position(game, map_x, map_y);
	if (door_idx == -1)
		return ;
	interact_with_door(game, door_idx);
}

int	check_door_at_offset(t_game *game, int dx, int dy)
{
	int	map_x;
	int	map_y;

	map_x = (int)game->player.play_x + dx;
	map_y = (int)game->player.play_y + dy;
	if (map_y < 0 || map_y >= game->map.height)
		return (-1);
	if (map_x < 0 || map_x >= game->map.width)
		return (-1);
	return (find_door_at_position(game, map_x, map_y));
}

void	check_nearby_doors(t_game *game)
{
	int	dx;
	int	dy;
	int	door_idx;

	dx = -1;
	while (dx <= 1)
	{
		dy = -1;
		while (dy <= 1)
		{
			door_idx = check_door_at_offset(game, dx, dy);
			if (door_idx != -1)
			{
				interact_with_door(game, door_idx);
				return ;
			}
			dy++;
		}
		dx++;
	}
}
