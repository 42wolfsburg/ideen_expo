/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:47:43 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 17:17:14 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// Return data pointer corresponding to pixel at (`x`,`y`)
unsigned char	*img_getloc(t_img *img, int x, int y)
{
	unsigned char	*loc;

	loc = img->data;
	loc += y * img->size_line;
	loc += x * (img->bpp / 8);
	return (loc);
}

/// Whether pixel at (`x`,`y`) is part of `img`
bool	img_inrange(t_img *img, int x, int y)
{
	return (x >= 0 && x < img->width && y >= 0 && y < img->height);
}

/// Read single pixel from image `img`
t_color	img_getpxl(t_img *img, int x, int y)
{
	if (!img_inrange(img, x, y))
		return (CTRANSPARENT);
	return (*((t_color *) img_getloc(img, x, y)));
}

/// Read single pixel, using relative coordinates (meaning 0 <= x,y <= 1)
t_color	img_getpxlr(t_img *img, float x, float y)
{
	const int	cx = x * img->width;
	const int	cy = y * img->height;

	return (img_getpxl(img, cx, cy));
}

/// Write single pixel from image `img`
void	img_putpxl(t_img *img, int x, int y, t_color c)
{
	if (!img_inrange(img, x, y))
		return ;
	*((t_color *) img_getloc(img, x, y)) = c;
}
