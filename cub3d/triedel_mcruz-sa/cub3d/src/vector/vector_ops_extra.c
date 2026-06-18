/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:42:23 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 12:45:13 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>
#include <math.h>

t_vec	vec_normalize(t_vec v)
{
	const float	len = vec_len(v);

	return (vec(v.x / len, v.y / len));
}

t_vec	vec_rotate(t_vec v, float r)
{
	t_vec	res;

	res.x = v.x * cos(r) - v.y * sin(r);
	res.y = v.x * sin(r) + v.y * cos(r);
	return (res);
}

int	vec_direction(t_vec *v)
{
	if (v->y < 0 && fabs(v->y) >= fabs(v->x))
		return (DNORTH);
	else if (v->x < 0 && fabs(v->x) >= fabs(v->y))
		return (DWEST);
	else if (v->y > 0 && fabs(v->y) >= fabs(v->x))
		return (DSOUTH);
	else if (v->x > 0 && fabs(v->x) >= fabs(v->y))
		return (DEAST);
	return (-1);
}

bool	vec_nonzero(t_vec *v)
{
	return (v->x != 0 || v->y != 0);
}

float	vec_mul(t_vec v, t_vec w)
{
	return (v.x * w.x + v.y * w.y);
}
