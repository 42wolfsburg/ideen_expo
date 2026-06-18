/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:44:05 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 15:52:46 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SQRT2	1.41421356237
#define SQRT3	1.73205080757
#define SQRT6	2.44948974278
#define SQRT3_6	0.707106781187
#define SQRT2_6	0.577350269188

#define SIN60	0.86602540378
#define COS60	0.5

#include <stdlib.h>
#include <stdio.h>

#include <mlx.h>
#include "load_fdf.h"
#include "display.h"

// const t_mat4 mat_camera = {
//   {  1,  0,  0,  0 },
//   {  0,  0,  1,  0 },
//   {  0,  1,  0,  -20 },
//   {  0,  0,  0,  1 }
// };

// const t_mat4 mat_camera = {
//   {  1,  0,  0,  0 },
//   {  0,  1,  0,  0 },
//   {  0,  0,  1,  0 },
//   {  0,  0,  0,  1 }
// };

// wikipedia
// t_mat4	mat_iso = {
//   {  SQRT3_6,  0,  -SQRT3_6,  0 },
//   {  1,  2,  1,  0 },
//   {  SQRT2_6,  -SQRT2_6,  SQRT2_6, 0 },
//   {  0,  0,  0,  1 }
// };

// t_mat4	mat_iso = {
//   {  -COS60, COS60, 0, 0 },
//   {  SIN60, SIN60, -1, 0 },
//   {  0, 0, 1, 0 },
//   {  0,  0,  0,  1 }
// };

// const t_mat4 mat_rot90 = {
// 	{ 1, -1, 0, 0 },
// 	{ 1, 0, 0, 0 },
// 	{ 0, 0, 1, 0 },
// 	{ 0, 0, 0, 1 }
// };

// const t_mat4 mat_camera = {
//   {1, 0, 0, 0},
//   {0, 1, 0, 0},
//   {0, 0, 1, 0},
//   {0, 1, 0, 1}
// };

// const float n = 0;
// const float f = 5;
// const float r = 1;
// const float l = -1;
// const float t = -1;
// const float b = 1;
// t_mat4 mat_persp = {
//   { 2 * n / (r - l), 0, 0, 0},
//   { 0, (2 * n) / (t - b), 0, 0},
//   { (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1},
//   { 0, 0, -(2 * f * n) / (f - n), 0 }
// };

// t_mat4 mat_ortho = {
//   { 2 / (r - l), 0, 0, -(r + l) / (r - l)},
//   { 0, 2 / (t - b), 0, -(t + b) / (t - b)},
//   { 0, 0, -2 / (f - n), -(f + n) / (f - n)},
//   { 0, 0, 0, 1 }
// };

// res.x = (SQRT3 * step * v.x - SQRT3 * step * v.y) / SQRT6;
// 	res.y = (SQRT3 * step * v.x + SQRT3 * step * v.y) / SQRT6;

bool	disp_init(t_disp *disp, int w, int h, char *title)
{
	disp->width = w;
	disp->height = h;
	disp->buffer = (t_image){.img = NULL};
	disp->models = NULL;
	disp->mod_active = 0;
	disp->mousex = -1;
	disp->mousey = -1;
	disp->showaxes = false;
	disp->mlx = mlx_init();
	if (!disp->mlx)
		return (false);
	disp->win = mlx_new_window(disp->mlx, w, h, title);
	if (!disp->win)
		return (false);
	disp_reset(disp);
	disp_hook(disp);
	return (true);
}

void	disp_hook(t_disp *disp)
{
	mlx_do_key_autorepeaton(disp->mlx);
	mlx_expose_hook(disp->win, event_expose, disp);
	mlx_hook(disp->win, DESTROYNOTIFY, NOEVENTMASK, event_destroy, disp);
	mlx_loop_hook(disp->mlx, disp_loop, disp);
	mlx_hook(disp->win, \
			KEYRELEASE, KEYRELEASEMASK | SHIFTMASK, event_keyup, disp);
	mlx_hook(disp->win, \
			KEYPRESS, KEYPRESSMASK | SHIFTMASK, event_keydown, disp);
	mlx_hook(disp->win, \
			BUTTONPRESS, BUTTONPRESSMASK, event_buttonpress, disp);
	mlx_hook(disp->win, \
			BUTTONRELEASE, BUTTONRELEASEMASK, event_buttonrelease, disp);
}

bool	disp_load(t_disp *disp, int nobj, char **files)
{
	int		i;
	t_model	*mod;
	t_list	*obj_node;

	i = -1;
	while (++i < nobj)
	{
		mod = model_load(files[i]);
		if (!mod)
			ft_printf("'%s' Load error\n", files[i]);
		obj_node = ft_lstnew(mod);
		if (!mod || !obj_node)
		{
			if (mod)
				free(mod);
			if (obj_node)
				free(obj_node);
			perror(files[i]);
			continue ;
		}
		ft_lstadd(&disp->models, obj_node);
	}
	if (ft_lstsize(disp->models) == 0)
		return (false);
	return (true);
}

void	disp_destroy(t_disp *disp)
{
	if (disp->buffer.img)
		mlx_destroy_image(disp->mlx, disp->buffer.img);
	if (disp->win)
		mlx_destroy_window(disp->mlx, disp->win);
	if (disp->mlx)
	{
		xmlx_destroy(disp->mlx);
		free(disp->mlx);
	}
	ft_lstclear(&disp->models, model_del);
}

int	disp_loop(t_disp *disp)
{
	if (disp->update)
		disp_draw(disp);
	disp->update = false;
	if (disp->autorot || disp->mouserot || disp->pan)
		disp->update = true;
	return (0);
}

/*
actual iso projections
*/
// t_fpoint	project_iso(t_cvec v)
// {
// 	t_fpoint	res;

// 	float step = 1;
// 	res.x = (SQRT3 * step * v.x - SQRT3 * step * v.y) / SQRT6;
// 	res.y = (SQRT3 * step * v.x + SQRT3 * step * v.y) / SQRT6;
// 	// res.x /= SQRT6;
// 	// res.y /= SQRT6;
// 	res.y -= step * v.z;
// 	res.x += .25;
// 	res.y += .5;
// 	// pt_scale(&res, 10);
// 	return (res);
// }

// int	main()
// {
// 	t_fpoint a = project((t_vec){1, 2, 3});
// 	printf("%f %f\n", a.x, a.y);
// }

/* 
same as demo
*/
// t_fpoint	project_iso(t_cvec v)
// {
// 	t_fpoint	res;

// 	float step = 0.001;
// 	res.x = sqrt(3) * step * v.x + sqrt(3) * step * v.y;
// 	res.y = sqrt(3) * step * v.y - sqrt(3) * step * v.x;
// 	res.x /= sqrt(6);
// 	res.y /= sqrt(6);
// 	res.y -= step * v.z;
// 	// res.x += .25;
// 	// res.y += .5;
// 	// pt_scale(&res, 10);
// 	return (res);
// }