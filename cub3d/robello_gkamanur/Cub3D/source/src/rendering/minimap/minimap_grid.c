/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:15:07 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:04:07 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	draw_minimap_cell(t_data *data, int map_x, int map_y, t_minimap *mm)
{
	int	color;
	int	screen_y;
	int	screen_x;

	color = get_minimap_color(data, map_x, map_y);
	screen_y = 0;
	while (screen_y < mm->scale)
	{
		screen_x = 0;
		while (screen_x < mm->scale)
		{
			put_pixel_to_img(&data->img, mm->offset_x + map_x * mm->scale
				+ screen_x, mm->offset_y + map_y * mm->scale + screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}

void	draw_minimap_grid(t_data *data, t_minimap *mm)
{
	int	map_y;
	int	map_x;

	map_y = 0;
	while (map_y < data->map.height)
	{
		map_x = 0;
		while (map_x < data->map.width)
		{
			draw_minimap_cell(data, map_x, map_y, mm);
			map_x++;
		}
		map_y++;
	}
}
