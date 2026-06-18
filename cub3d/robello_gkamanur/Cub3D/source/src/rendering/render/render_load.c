/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:36:43 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:05:15 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

int	load_texture(t_data *data, t_img *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		printf("Error\nFailed to get texture data\n");
		return (0);
	}
	tex->width = width;
	tex->height = height;
	return (1);
}

int	load_wall_textures(t_data *data)
{
	if (!load_texture(data, &data->textures.north_img, data->textures.north))
		return (0);
	if (!load_texture(data, &data->textures.south_img, data->textures.south))
		return (0);
	if (!load_texture(data, &data->textures.west_img, data->textures.west))
		return (0);
	if (!load_texture(data, &data->textures.east_img, data->textures.east))
		return (0);
	return (1);
}

int	load_floor_ceiling_textures(t_data *data)
{
	if (data->textures.floor_tex)
	{
		if (!load_texture(data, &data->textures.floor_img,
				data->textures.floor_tex))
			return (0);
		data->use_floor_texture = 1;
		printf("✓ Floor texture loaded\n");
	}
	if (data->textures.ceiling_tex)
	{
		if (!load_texture(data, &data->textures.ceiling_img,
				data->textures.ceiling_tex))
			return (0);
		data->use_ceiling_texture = 1;
		printf("✓ Ceiling texture loaded\n");
	}
	return (1);
}

int	load_textures(t_data *data)
{
	if (!load_wall_textures(data))
		return (0);
	if (!load_floor_ceiling_textures(data))
		return (0);
	printf("✓ Textures loaded\n");
	return (1);
}
