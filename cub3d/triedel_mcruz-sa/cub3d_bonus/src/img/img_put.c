/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:51:56 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 11:52:22 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	img_put_img_section_stencil(t_img *dst, t_imgsec *src,
			t_ipt dstpos, t_color col)
{
	int			y;
	int			x;
	t_color		c;
	float		f;

	y = 0;
	while (y < src->sec.br.y - src->sec.tl.y)
	{
		x = 0;
		while (x < src->sec.br.x - src->sec.tl.x)
		{
			c = img_getpxl(src->img, x + src->sec.tl.x, y + src->sec.tl.y);
			f = (0xff & c) / (float) 0xff;
			if ((c & 0xffffff) != 0)
				img_putpxl(dst, dstpos.x + x, dstpos.y + y, col_lum(col, f));
			x++;
		}
		y++;
	}
}

void	img_put_img(t_img *dst, t_img *src, int putx, int puty)
{
	int		y;
	int		x;
	t_color	c;

	y = 0;
	while (y < src->height * src->scale)
	{
		x = 0;
		while (x < src->width * src->scale)
		{
			c = img_getpxl(src, x / src->scale, y / src->scale);
			if ((c & 0xffffff) != 0 && c != 0xffffff)
				img_putpxl(dst, putx + x, puty + y, c);
			x++;
		}
		y++;
	}
}

void	img_put_img_mid(t_img *dst, t_img *src, int putx, int puty)
{
	img_put_img(dst, src, putx - src->width / 2, puty - src->height / 2);
}
