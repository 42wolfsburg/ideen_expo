/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:49:21 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/23 14:21:07 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	fill_pixels_batch(int *pixels, int start, int end, int color)
{
	int	i;
	int	batch_size;

	batch_size = 8;
	i = start;
	while (i <= end - batch_size)
	{
		pixels[i] = color;
		pixels[i + 1] = color;
		pixels[i + 2] = color;
		pixels[i + 3] = color;
		pixels[i + 4] = color;
		pixels[i + 5] = color;
		pixels[i + 6] = color;
		pixels[i + 7] = color;
		i += batch_size;
	}
	while (i < end)
		pixels[i++] = color;
}

void	fast_background_fill(t_data *data, int ceiling_color, int floor_color)
{
	int	*pixels;
	int	total_pixels;
	int	half_screen;

	pixels = (int *)data->img.addr;
	total_pixels = WIN_WIDTH * WIN_HEIGHT;
	half_screen = total_pixels / 2;
	fill_pixels_batch(pixels, 0, half_screen, ceiling_color);
	fill_pixels_batch(pixels, half_screen, total_pixels, floor_color);
}

int	should_use_low_quality(double distance)
{
	if (WIN_WIDTH >= 3000 && distance > 10.0)
		return (1);
	else if (WIN_WIDTH >= 2000 && distance > 15.0)
		return (1);
	return (0);
}
