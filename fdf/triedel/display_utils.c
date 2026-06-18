/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:27:04 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 12:51:34 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	disp_reset(t_disp *disp)
{
	disp->shift = false;
	disp->zoom = 0.75;
	disp->z_size = 1.0;
	disp->ticks = 0;
	disp->yaw = 0;
	disp->roll = 0;
	disp->center.x = disp->width / 2;
	disp->center.y = disp->height / 2;
	disp->center_old = disp->center;
	disp->autorot = false;
	disp->mouserot = false;
	disp->update = true;
	disp->pan = false;
	disp->dragstart = pt(-1, -1);
}
