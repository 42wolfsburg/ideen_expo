/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:53:59 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 12:46:10 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>
#include <math.h>
#include <stdio.h>

/* ===== vec ===== */
t_vec	vec(float x, float y)
{
	return ((t_vec){x, y});
}

void	vec_print(t_pt *p)
{
	printf("vec: %5.1f %5.1f\n", p->x, p->y);
}

t_vec	vec_from_vec3(t_vec3 *v)
{
	return (vec(v->x, v->y));
}
