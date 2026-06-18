/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:41:42 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 21:20:09 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_column_segment(t_game *game, t_ray *ray, t_img *tex, int tex_x)
{
	double	tex_pos;
	double	step;
	int		y;
	int		color;
	int		x;

	x = ray->column_x;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - game->win_h / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		if (tex_x != -1)
		{
			color = *(int *)(tex->addr + (((int)tex_pos & (tex->height - 1))
						* tex->linen + tex_x * (tex->bpp / 8)));
			my_mlx_pixel_put(&game->frame.img, x, y, color);
		}
		tex_pos = tex_pos + step;
		y = y + 1;
	}
}

int	ft_process_cell(t_game *game, t_ray *ray, char cell)
{
	int	door_idx;

	door_idx = check_cell_for_door(game, ray->map_x, ray->map_y);
	if (door_idx != -1)
		return (process_door_cell(game, ray, door_idx));
	if (cell == WALL)
	{
		ray->is_door = 0;
		return (1);
	}
	return (0);
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	int		tex_x;

	ray->column_x = x;
	if (ray->is_door == 0)
	{
		tex = ft_select_wall_texture(game, ray);
		if (!tex || !tex->img)
			return ;
		tex_x = get_texture_x(game, ray, tex);
		draw_column_segment(game, ray, tex, tex_x);
		return ;
	}
	tex = select_door_texture(game, ray);
	if (!tex || !tex->img)
		return ;
	tex_x = get_door_tex_x(game, ray, tex);
	if (tex_x == -1)
		return ;
	draw_column_segment(game, ray, tex, tex_x);
}

void	calculate_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.play_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = game->player.play_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)game->tex.tex[WALL_N].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = game->tex.tex[WALL_N].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = game->tex.tex[WALL_N].width - ray->tex_x - 1;
}

void	calculate_wall_dimensions(t_game *game, t_ray *ray)
{
	ray->line_height = (int)(game->win_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->win_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_h / 2;
	if (ray->draw_end >= game->win_h)
		ray->draw_end = game->win_h - 1;
}
