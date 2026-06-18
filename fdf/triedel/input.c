/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:57:32 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 09:22:24 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	keys_handle_view(t_disp *disp, int key)
{
	if (key == XK_R)
	{
		disp->autorot = !disp->autorot;
		disp->ticks = 0;
		disp->yaw = 0;
		disp->update = true;
	}
	if (key == XK_C)
		disp_reset(disp);
	if (key == XK_SPACE)
		disp->mouserot = !disp->mouserot;
	if (key == XK_M)
	{
		disp->mod_active = (disp->mod_active + \
				ft_lstsize(disp->models) - 1) % ft_lstsize(disp->models);
		ft_printf("%s\n", disp_getmodel(disp)->name);
	}
	if (key == XK_N)
	{
		disp->mod_active = (disp->mod_active + \
				ft_lstsize(disp->models) + 1) % ft_lstsize(disp->models);
		ft_printf("%s\n", disp_getmodel(disp)->name);
	}
}

void	keys_handle_rot(t_disp *disp, int key)
{
	if (key == XK_D)
		disp->yaw += 45;
	if (key == XK_A)
		disp->yaw -= 45;
	if (key == XK_W)
		disp->roll -= 45;
	if (key == XK_S)
		disp->roll += 45;
	if (key == XK_LEFT)
		disp->yaw -= 10;
	if (key == XK_RIGHT)
		disp->yaw += 10;
	if (key == XK_UP)
		disp->roll -= 10;
	if (key == XK_DOWN)
		disp->roll += 10;
}

void	mouse_handle_zoom(t_disp *disp, int button)
{
	if (button == 7 || (button == 5 && disp->shift))
	{
		disp->z_size *= 0.75;
		disp->update = true;
	}
	if (!disp->shift && (button == 4 || button == 5))
	{
		(button == 4) && (disp->zoom *= 1.25);
		(button == 5) && (disp->zoom *= .75);
		disp->update = true;
	}
}
