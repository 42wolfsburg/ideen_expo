/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:36:23 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 12:48:46 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <mlx.h>
#include <libft.h>

#include "display.h"

void	line_init(struct s_linestate *ls, t_cpoint p1, t_cpoint p2)
{
	ls->dx = abs(p2.x - p1.x);
	ls->sx = ft_ternary_int(p1.x < p2.x, 1, -1);
	ls->dy = -abs(p2.y - p1.y);
	ls->sy = ft_ternary_int(p1.y < p2.y, 1, -1);
	ls->error = ls->dx + ls->dy;
	ls->steps = ft_max(ls->dx, -ls->dy);
	ls->i = 0;
	ls->interpol = (p1.col != p2.col);
	ls->col = p1.col;
}

t_image	img_new(void *mlx, int width, int height)
{
	t_image	retval;

	retval.img = mlx_new_image(mlx, width, height);
	retval.data = NULL;
	retval.width = width;
	retval.height = height;
	if (retval.img)
		retval.data = mlx_get_data_addr(retval.img, &retval.bpp, \
				&retval.linelen, &retval.endian);
	return (retval);
}

bool	img_putpxl(t_image *img, int x, int y, unsigned int value)
{
	char	*dat;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (false);
	dat = (char *) img->data;
	dat += y * img->linelen;
	dat += x * (img->bpp / 8);
	*((unsigned int *) dat) = cl_add(*((t_color *) dat), clt_to_cl(value));
	return (true);
}

void	img_line(t_image *img, t_cpoint p1, t_cpoint p2)
{
	struct s_linestate	ls;

	line_init(&ls, p1, p2);
	while (true)
	{
		if (ls.interpol)
			ls.col = cl_interpol(p1.col, p2.col, ls.i++, ls.steps);
		img_putpxl(img, p1.x, p1.y, ls.col);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		ls.e2 = 2 * ls.error;
		if ((ls.e2 >= ls.dy && p1.x == p2.x) || \
					(ls.e2 <= ls.dx && p1.y == p2.y))
			break ;
		if (ls.e2 >= ls.dy)
		{
			ls.error += ls.dy;
			p1.x += ls.sx;
		}
		if (ls.e2 <= ls.dx)
		{
			ls.error += ls.dx;
			p1.y += ls.sy;
		}
	}
}

// void	img_line(t_image *img, t_point p1, t_point p2)
// {
// 	img_line_cl(img, p1, p2, 0xffffff);
// }

// void	img_print(t_image *img)
// {
// 	printf("%ix%i: %p\n", img->width, img->height, img->img);
// 	printf("data: %p\n", img->data);
// 	printf("bpp: %i\n", img->bpp);
// 	printf("linelen: %i\n", img->linelen);
// 	printf("endian: %i\n", img->endian);
// }
