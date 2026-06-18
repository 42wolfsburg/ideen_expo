/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CCC.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:14:07 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 22:47:01 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	handle_window_close(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

void	move_ray_x(t_ray *ray)
{
	ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;
	ray->map_x = ray->map_x + ray->step_x;
	ray->side = 0;
}

void	move_ray_y(t_ray *ray)
{
	ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
	ray->map_y = ray->map_y + ray->step_y;
	ray->side = 1;
}

void	set_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

double	calc_tex_pos(t_game *game, t_ray *ray, double step)
{
	double	tex_pos;

	tex_pos = (ray->draw_start - game->win_h / 2
			+ ray->line_height / 2) * step;
	return (tex_pos);
}
