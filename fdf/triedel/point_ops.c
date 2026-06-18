/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:32:26 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 10:33:39 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	fpt_scale(t_fpoint *p, float f)
{
	p->x *= f;
	p->y *= f;
}

void	fpt_translate(t_fpoint *p, t_fpoint q)
{
	p->x += q.x;
	p->y += q.y;
}
