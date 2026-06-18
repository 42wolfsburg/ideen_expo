/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:48:40 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/23 14:21:19 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	draw_wall_column(t_data *data, t_ray *ray, t_img *tex, int x)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	tex_x = calc_texture_x(ray, tex);
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	while (ray->draw_start < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel_to_img(&data->img, x, ray->draw_start, color);
		ray->draw_start++;
	}
}

void	cast_ray(t_data *data, int x)
{
	t_ray	ray;
	t_img	*texture;

	init_ray_params(data, x, &ray);
	init_ray_params_y(data, &ray);
	perform_dda(data, &ray);
	calc_wall_params(data, &ray);
	texture = select_wall_texture(data, &ray);
	draw_wall_column(data, &ray, texture, x);
}

void	dup_col_raycast(t_data *data, int x, int step)
{
	int		dup;
	int		y;
	int		bpp;
	char	*src_col;
	char	*dst_col;

	bpp = data->img.bits_per_pixel / 8;
	dup = 1;
	while (dup < step && (x + dup) < WIN_WIDTH)
	{
		src_col = data->img.addr + (x * bpp);
		dst_col = data->img.addr + ((x + dup) * bpp);
		y = 0;
		while (y < WIN_HEIGHT)
		{
			*(unsigned int *)(dst_col + y
					* data->img.line_length) = *(unsigned int *)(src_col + y
					* data->img.line_length);
			y++;
		}
		dup++;
	}
}

int	get_raycast_step(void)
{
	if (WIN_WIDTH >= 3000)
		return (3);
	else if (WIN_WIDTH >= 2000)
		return (2);
	else if (WIN_WIDTH >= 1600)
		return (2);
	else
		return (1);
}

void	raycast(t_data *data)
{
	int	x;
	int	step;

	step = get_raycast_step();
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(data, x);
		if (step > 1)
			dup_col_raycast(data, x, step);
		x += step;
	}
}
