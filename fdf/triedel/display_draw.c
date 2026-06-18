/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:13:59 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 15:53:07 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "display.h"

void	disp_draw(t_disp *disp)
{
	disp->ticks++;
	if (disp->buffer.img)
		mlx_destroy_image(disp->mlx, disp->buffer.img);
	disp->buffer = img_new(disp->mlx, disp->width, disp->height);
	if (!disp->buffer.img)
		event_destroy((void *) disp);
	xmlx_mouse_get_pos(disp->mlx, disp->win, &disp->mousex, &disp->mousey);
	if (disp->pan && disp->mousex != -1)
	{
		if (disp->dragstart.x == -1)
			disp->dragstart = pt(disp->mousex, disp->mousey);
		disp->center.x = disp->center_old.x + \
				(disp->mousex - disp->dragstart.x);
		disp->center.y = disp->center_old.y + \
				(disp->mousey - disp->dragstart.y);
	}
	disp_frame_init(disp);
	disp_draw_axes(disp);
	disp_draw_model(disp);
	mlx_put_image_to_window(disp->mlx, disp->win, disp->buffer.img, 0, 0);
	mlx_do_sync(disp->mlx);
}

void	disp_draw3dline(t_disp *disp, t_cvec v, t_cvec w)
{
	t_fpoint	p;
	t_fpoint	q;

	p = fpt_from_vec(disp_project_cvv(disp, vec_from_cvec(v)));
	q = fpt_from_vec(disp_project_cvv(disp, vec_from_cvec(w)));
	fpt_translate(&p, fpt(disp->center.x, disp->center.y));
	fpt_translate(&q, fpt(disp->center.x, disp->center.y));
	img_line(&disp->buffer, cpt(p.x, p.y, v.col), cpt(q.x, q.y, w.col));
}

void	disp_draw_axes(t_disp *disp)
{
	if (disp->showaxes)
	{
		disp_draw3dline(disp, cvec(0, 0, 0, C_RED), cvec(1, 0, 0, C_RED));
		disp_draw3dline(disp, cvec(0, 0, 0, C_GREEN), cvec(0, 1, 0, C_GREEN));
		disp_draw3dline(disp, cvec(0, 0, 0, C_BLUE), cvec(0, 0, 1, C_BLUE));
	}
}

void	disp_draw_model(t_disp *disp)
{
	t_model			*mod;
	t_edge			e;
	unsigned int	i;

	mod = disp_getmodel(disp);
	if (!mod)
		return ;
	i = 0;
	while (i < mod->nedges)
	{
		e = mod->edges[i];
		disp_draw3dline(disp, mod->verts[e.a], mod->verts[e.b]);
		i++;
	}
}
