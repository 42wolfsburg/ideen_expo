/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:33:11 by loandrad          #+#    #+#             */
/*   Updated: 2023/06/08 14:48:59 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	interpolate(int startcolor, int endcolor, double fraction)
{
	int	red;
	int	green;
	int	blue;

	red = ((endcolor >> 16) - (startcolor >> 16))
		* fraction + (startcolor >> 16);
	green = ((endcolor >> 8 & 0xFF) - (startcolor >> 8 & 0xFF))
		* fraction + (startcolor >> 8 & 0xFF);
	blue = ((endcolor & 0xFF) - (startcolor & 0xFF))
		* fraction + (startcolor & 0xFF);
	return (0xFF << 24 | red << 16 | green << 8 | blue);
}

static void	color_set(t_fractol *f, int color)
{
	int		i;
	int		j;
	double	fraction;
	int		color1;
	int		color2;

	color1 = 0xFFFFFF;
	color2 = color;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{
			fraction = (double)j / (MAX_ITERATIONS / 2);
			f->palette[i + j] = interpolate(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = 0x000000;
		i += j;
	}
	f->palette[MAX_ITERATIONS - 1] = 0;
}

void	toggle_color(t_fractol *f)
{
	int	colors[4];

	colors[0] = 0xDC143C;
	colors[1] = 0xFFD700;
	colors[2] = 0x2F4F4F;
	colors[3] = 0xFF1493;
	reinit_img(f);
	color_set(f, colors[f->color_count]);
	if (f->color_count == 3)
		f->color_count = 0;
	else
		f->color_count++;
}
