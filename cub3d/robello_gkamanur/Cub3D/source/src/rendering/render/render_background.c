/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:41:11 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:39:46 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	render_background_color(t_data *data)
{
	int	*pixels;
	int	ceiling_color;
	int	floor_color;
	int	half_pixels;

	ceiling_color = (data->ceiling.r << 16) | (data->ceiling.g << 8)
		| data->ceiling.b;
	floor_color = (data->floor.r << 16) | (data->floor.g << 8) | data->floor.b;
	pixels = (int *)data->img.addr;
	half_pixels = (WIN_WIDTH * WIN_HEIGHT) / 2;
	fill_pixels_unrolled(pixels, 0, half_pixels, ceiling_color);
	fill_pixels_unrolled(pixels, half_pixels, WIN_WIDTH * WIN_HEIGHT,
		floor_color);
}

void	render_background_texture(t_data *data)
{
	render_ceiling(data);
	render_floor(data);
}

void	render_background(t_data *data)
{
	if ((data->use_ceiling_texture || data->use_floor_texture)
		&& data->texture_mode)
		render_background_texture(data);
	else
		render_background_color(data);
}
