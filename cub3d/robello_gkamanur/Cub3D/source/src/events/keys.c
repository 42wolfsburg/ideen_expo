/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:24:32 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 20:34:49 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

int	handle_escape(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		printf("ESC pressed - Closing...\n");
		destroy_window(data);
		exit(0);
	}
	return (0);
}

int	handle_movement_keys(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		move_forward(data);
	else if (keycode == KEY_S)
		move_backward(data);
	else if (keycode == KEY_A)
		strafe_right(data);
	else if (keycode == KEY_D)
		strafe_left(data);
	else
		return (0);
	return (1);
}

int	handle_rotation_keys(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		rotate_left(data);
	else if (keycode == KEY_RIGHT)
		rotate_right(data);
	else
		return (0);
	return (1);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (handle_escape(keycode, data))
		return (0);
	if (handle_movement_keys(keycode, data))
		return (0);
	if (handle_rotation_keys(keycode, data))
		return (0);
	return (0);
}
