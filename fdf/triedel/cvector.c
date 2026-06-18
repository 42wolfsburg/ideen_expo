/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:53:08 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 08:41:42 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_cvec	cvec_translate(t_cvec v, t_cvec w)
{
	v.x += w.x;
	v.y += w.y;
	v.z += w.z;
	return (v);
}

t_cvec	cvec_inv(t_cvec v)
{
	return ((t_cvec){.x = -v.x, .y = -v.y, .z = -v.z, .col = v.col});
}

t_cvec	cvec(float x, float y, float z, t_color cl)
{
	return ((t_cvec){.x = x, .y = y, .z = z, .col = cl});
}

void	cvec_setminmax(t_cvec *v, t_vec *min, t_vec *max)
{
	if (v->x < min->x)
		min->x = v->x;
	if (v->y < min->y)
		min->y = v->y;
	if (v->z < min->z)
		min->z = v->z;
	if (v->x > max->x)
		max->x = v->x;
	if (v->y > max->y)
		max->y = v->y;
	if (v->z > max->z)
		max->z = v->z;
}
