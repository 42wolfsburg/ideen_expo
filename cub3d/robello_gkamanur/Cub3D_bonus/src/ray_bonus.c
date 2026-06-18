/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:40:52 by robello           #+#    #+#             */
/*   Updated: 2026/01/08 22:40:52 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	process_door_cell(t_game *game, t_ray *ray, int door_idx)
{
	t_door	*door;
	double	hit_x;
	double	left_edge;
	double	right_edge;

	door = &game->doors.list[door_idx];
	if (door->is_secret == SECRET_DOOR_YES && door->revealed == 0)
		return (1);
	if (ray->side == 0)
		hit_x = game->player.play_y + (ray->side_dist_x
				- ray->delta_dist_x) * ray->ray_dir_y;
	else
		hit_x = game->player.play_x + (ray->side_dist_y
				- ray->delta_dist_y) * ray->ray_dir_x;
	hit_x = hit_x - floor(hit_x);
	left_edge = (1.0 - door->door_progress) * 0.5;
	right_edge = 1.0 - left_edge;
	if (hit_x < left_edge || hit_x > right_edge)
	{
		ray->is_door = 1;
		ray->door_idx = door_idx;
		return (1);
	}
	return (0);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	char	cell;

	ray->is_door = 0;
	ray->door_idx = -1;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			move_ray_x(ray);
		else
			move_ray_y(ray);
		cell = game->map.map[ray->map_y][ray->map_x];
		if (ft_process_cell(game, ray, cell))
			ray->hit = 1;
	}
	set_perp_dist(ray);
}

void	calc_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.play_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.play_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.play_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.play_y)
			* ray->delta_dist_y;
	}
}

void	ft_init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)game->win_w - 1;
	ray->ray_dir_x = game->player.playdir_x
		+ game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.playdir_y
		+ game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.play_x;
	ray->map_y = (int)game->player.play_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	ft_castrays(t_game *game)
{
	t_ray	ray;
	int		x;

	if (!game->sprites.zbuffer || game->sprites.zbuffer_w != game->win_w)
	{
		free(game->sprites.zbuffer);
		game->sprites.zbuffer = malloc(sizeof(double) * game->win_w);
		if (!game->sprites.zbuffer)
			return ;
		game->sprites.zbuffer_w = game->win_w;
	}
	x = 0;
	while (x < game->win_w)
	{
		ft_init_ray(game, &ray, x);
		ray.column_x = x;
		calc_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calculate_wall_dimensions(game, &ray);
		calculate_wall_texture(game, &ray);
		draw_wall_column(game, &ray, x);
		game->sprites.zbuffer[x] = ray.perp_wall_dist;
		x++;
	}
}
