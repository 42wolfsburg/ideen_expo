/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:24:18 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:04:54 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	calc_wall_params(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.y + (1 - ray->step_y)
				/ 2) / ray->dir_y;
	if (ray->perp_wall_dist <= 0)
		ray->perp_wall_dist = 0.01;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

t_img	*select_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&data->textures.west_img);
		else
			return (&data->textures.east_img);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&data->textures.north_img);
		else
			return (&data->textures.south_img);
	}
}

int	calc_texture_x(t_ray *ray, t_img *texture)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}
