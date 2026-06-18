/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:25:55 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 10:36:06 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "display.h"

t_point	pt(int x, int y)
{
	return ((t_point){.x = x, .y = y});
}

t_cpoint	cpt(int x, int y, t_color col)
{
	return ((t_cpoint){.x = x, .y = y, .col = col});
}

t_fpoint	fpt(float x, float y)
{
	return ((t_fpoint){.x = x, .y = y});
}

t_fpoint	fpt_from_vec(t_vec v)
{
	return (fpt(v.x, v.y));
}
