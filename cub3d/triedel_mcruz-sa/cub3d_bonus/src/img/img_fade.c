/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_fade.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:09:57 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 13:29:04 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	img_green_fade(t_img *img)
{
	int		y;
	int		x;
	t_color	c;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			c = img_getpxl(img, x, y);
			if ((c & 0xff0000) >> 4 * 4 > 0x4d)
				c = CGREEN;
			c = col_lum(c, MATTEX_FADE);
			if ((0xff00 & c) <= MATTEX_BACK)
				c = MATTEX_BACK;
			img_putpxl(img, x, y, c);
			x++;
		}
		y++;
	}
}
