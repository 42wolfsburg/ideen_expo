/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_project.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:19:29 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 12:55:15 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "display.h"

void	disp_frame_init_rot(t_disp *disp)
{
	t_mat4	tmp;

	if (disp->mouserot)
	{
		mat_rotation(tmp, (float)(disp->height / 2 - disp->mousey) / \
				disp->height * M_PI, 0, 0);
		matmul(disp->mat, tmp);
		mat_rotation(tmp, 0, 0, (float)(disp->width / 2 - disp->mousex) / \
				disp->width * M_PI);
		matmul(disp->mat, tmp);
	}
	else
	{
		mat_rotation(tmp, (90.0 - 35.264 + disp->roll) / 180 * M_PI, 0, 0);
		matmul(disp->mat, tmp);
	}
	mat_rotation(tmp, 0, 0, (-45.0 + disp->yaw) / 180 * M_PI);
	matmul(disp->mat, tmp);
	if (disp->autorot)
	{
		mat_rotation(tmp, 0, 0, (float) disp->ticks / 400 * 2 * M_PI);
		matmul(disp->mat, tmp);
		disp->update = true;
	}
}

void	disp_frame_init(t_disp *disp)
{
	t_mat4	tmp;

	mat_identity(disp->mat);
	mat_identity(tmp);
	matmul(disp->mat, tmp);
	mat_identity(tmp);
	tmp[3][3] = 1 / ((float) disp->zoom * disp->height / 2);
	matmul(disp->mat, tmp);
	disp_frame_init_rot(disp);
	mat_identity(tmp);
	tmp[2][2] = disp->z_size;
	matmul(disp->mat, tmp);
}

t_model	*disp_getmodel(t_disp *disp)
{
	return ((t_model *) ft_lstget(disp->models, disp->mod_active)->content);
}

t_fpoint	disp_project(t_disp *disp, t_vec v)
{
	t_vec4	v4;

	v4 = vecmul(disp->mat, vec_from_vec4(v));
	v = vec_normalize(v4);
	return (fpt(v.x, v.y));
}

t_vec	disp_project_cvv(t_disp *disp, t_vec v)
{
	t_vec4	v4;

	v4 = vecmul(disp->mat, vec_from_vec4(v));
	return (vec_normalize(v4));
}
