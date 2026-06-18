/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:43:20 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:23:13 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_door_tex_x(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.play_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.play_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	check_cell_for_door(t_game *game, int map_x, int map_y)
{
	int	idx;

	idx = 0;
	while (idx < game->doors.count)
	{
		if (game->doors.list[idx].door_x == map_x
			&& game->doors.list[idx].door_y == map_y)
		{
			return (idx);
		}
		idx = idx + 1;
	}
	return (-1);
}

void	handle_door_hit(t_game *game, t_ray *ray, int door_idx)
{
	t_door	*door;

	door = &game->doors.list[door_idx];
	ray->hit = 1;
	if (door->is_secret == SECRET_DOOR_YES)
	{
		if (door->revealed == 0)
		{
			ray->is_door = 0;
			return ;
		}
	}
	ray->is_door = 1;
	ray->door_idx = door_idx;
}

void	check_hit_type(t_game *game, t_ray *ray, char cell)
{
	int	door_idx;

	if (cell == WALL)
	{
		ray->hit = 1;
		ray->is_door = 0;
		return ;
	}
	door_idx = check_cell_for_door(game, ray->map_x, ray->map_y);
	if (door_idx != -1)
	{
		handle_door_hit(game, ray, door_idx);
		return ;
	}
}

t_img	*select_door_texture(t_game *game, t_ray *ray)
{
	t_door	*door;
	t_img	*tex;

	if (ray->is_door == 0)
		return (NULL);
	if (ray->door_idx == -1)
		return (NULL);
	if (ray->door_idx < 0 || ray->door_idx >= game->doors.count)
		return (NULL);
	door = &game->doors.list[ray->door_idx];
	if (door->is_secret == SECRET_DOOR_YES)
	{
		if (door->revealed == 0)
			return (NULL);
		tex = &game->tex.tex[T_SECRET_D];
	}
	else
		tex = &game->tex.tex[T_DOOR];
	if (!tex->img)
		return (NULL);
	return (tex);
}
