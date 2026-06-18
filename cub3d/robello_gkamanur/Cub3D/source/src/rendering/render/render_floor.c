/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:44:08 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:05:10 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	render_floor_textured(t_data *data)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = WIN_HEIGHT / 2 - 1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			tex_x = (x * data->textures.floor_img.width) / WIN_WIDTH;
			tex_y = ((y - WIN_HEIGHT / 2) * data->textures.floor_img.height)
				/ (WIN_HEIGHT / 2);
			color = get_texture_pixel(&data->textures.floor_img, tex_x, tex_y);
			put_pixel_to_img(&data->img, x, y, color);
		}
	}
}

void	render_floor_color(t_data *data, int color)
{
	int	x;
	int	y;

	y = WIN_HEIGHT / 2 - 1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			put_pixel_to_img(&data->img, x, y, color);
	}
}

void	render_floor(t_data *data)
{
	int	color;

	if (data->use_floor_texture && data->texture_mode)
		render_floor_textured(data);
	else
	{
		color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
		render_floor_color(data, color);
	}
}
