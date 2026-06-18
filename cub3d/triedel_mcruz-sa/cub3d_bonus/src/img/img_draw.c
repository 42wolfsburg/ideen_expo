/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:48:36 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 11:50:56 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// draw rectangle from top left to bottom right
void	img_draw_rect(t_img *img, t_ipt tl, t_ipt br, t_color col)
{
	int	x;
	int	y;

	y = tl.y;
	while (y <= br.y)
	{
		x = tl.x;
		while (x <= br.x)
		{
			img_putpxl(img, x, y, col);
			x++;
		}
		y++;
	}
}

/// paint complete image with color `col`
void	img_clear(t_img *img, t_color col)
{
	img_draw_rect(img, ipt(0, 0), ipt(img->width - 1, img->height - 1), col);
}

static void	img_line_init(struct s_linestate *ls, t_ipt p1, t_ipt p2)
{
	ls->dx = abs(p2.x - p1.x);
	ls->sx = ft_ternary_int(p1.x < p2.x, 1, -1);
	ls->dy = -abs(p2.y - p1.y);
	ls->sy = ft_ternary_int(p1.y < p2.y, 1, -1);
	ls->error = ls->dx + ls->dy;
	ls->steps = fmax(ls->dx, -ls->dy);
	ls->i = 0;
}

void	img_draw_line(t_img *img, t_ipt p1, t_ipt p2, t_color col)
{
	struct s_linestate	ls;

	img_line_init(&ls, p1, p2);
	while (true)
	{
		img_putpxl(img, p1.x, p1.y, col);
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
