/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:53:23 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 12:58:26 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <mlx.h>

/// Create new image `img` with width `w` and height `h`
void	img_init(t_img *img, void *mlx, int w, int h)
{
	img->mlximg = mlx_new_image(mlx, w, h);
	if (!img->mlximg)
		return ;
	img->width = w;
	img->height = h;
	img->data = (unsigned char *) mlx_get_data_addr(img->mlximg,
			&img->bpp, &img->size_line, &img->endian);
	img->scale = 1;
}

/// Create new image `img` by reading and .xpm file from `path`
bool	img_load(t_img *img, void *mlx, char *path)
{
	img->mlximg = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->mlximg)
		img->mlximg = (unsigned char *) mlx_xpm_file_to_image(mlx,
				TEX_NOTFOUND, &img->width, &img->height);
	if (!img->mlximg)
		return (false);
	img->data = (unsigned char *) mlx_get_data_addr(img->mlximg,
			&img->bpp, &img->size_line, &img->endian);
	img->scale = 1;
	return (true);
}

/// Deinit image `img`
void	img_deinit(t_img *img, void *mlx)
{
	if (img && img->mlximg)
		mlx_destroy_image(mlx, img->mlximg);
}
