/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:06:44 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 09:21:01 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	event_buttonpress(int button, int x, int y, void *param)
{
	t_disp	*disp;

	disp = (t_disp *) param;
	if (button == 3)
	{
		disp->dragstart = pt(-1, -1);
		disp->center_old = disp->center;
		disp->pan = true;
		disp->update = true;
	}
	if (button == 6 || (button == 4 && disp->shift))
	{
		disp->z_size *= 1.5;
		disp->update = true;
	}
	if (button == 1)
	{
		disp->center = pt(x, y);
		disp->update = true;
	}
	mouse_handle_zoom(disp, button);
	return (0);
}

int	event_buttonrelease(int button, int x, int y, void *param)
{
	t_disp	*disp;

	(void) x;
	(void) y;
	disp = (t_disp *) param;
	if (button == 3)
	{
		disp->pan = false;
		disp->dragstart = pt(-1, -1);
	}
	return (0);
}
