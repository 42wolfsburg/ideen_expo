/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:42:53 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:41:04 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	render_ceiling_textured(t_data *data)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			tex_x = (x * data->textures.ceiling_img.width) / WIN_WIDTH;
			tex_y = (y * data->textures.ceiling_img.height) / (WIN_HEIGHT / 2);
			color = get_texture_pixel(&data->textures.ceiling_img, tex_x,
					tex_y);
			put_pixel_to_img(&data->img, x, y, color);
		}
	}
}

void	render_ceiling_color(t_data *data, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			put_pixel_to_img(&data->img, x, y, color);
	}
}

void	render_ceiling(t_data *data)
{
	int	color;

	if (data->use_ceiling_texture && data->texture_mode)
		render_ceiling_textured(data);
	else
	{
		color = (data->ceiling.r << 16) | (data->ceiling.g << 8)
			| data->ceiling.b;
		render_ceiling_color(data, color);
	}
}
