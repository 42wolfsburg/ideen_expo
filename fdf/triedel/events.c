/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:53:08 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 15:53:16 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "display.h"

int	event_keydown(int key, void *arg)
{
	t_disp	*disp;

	disp = (t_disp *) arg;
	if (key == XK_SHIFT_L || key == XK_SHIFT_R)
		disp->shift = true;
	if (key == XK_X || key == XK_ESCAPE)
		event_destroy((void *) disp);
	if (key == XK_V)
		disp->showaxes = !disp->showaxes;
	keys_handle_view(disp, key);
	keys_handle_rot(disp, key);
	disp->update = true;
	return (0);
}

int	event_keyup(int key, void *arg)
{
	t_disp	*disp;

	disp = (t_disp *) arg;
	if (key == XK_SHIFT_L || key == XK_SHIFT_R)
		disp->shift = false;
	return (0);
}

int	event_expose(void *arg)
{
	t_disp	*disp;

	disp = (t_disp *) arg;
	disp->update = true;
	return (0);
}

int	event_destroy(void *arg)
{
	disp_destroy((t_disp *) arg);
	exit(0);
}
