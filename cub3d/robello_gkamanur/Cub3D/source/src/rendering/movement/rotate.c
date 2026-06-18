/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:09:55 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:04:19 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

int	is_valid_position(t_data *data, double x, double y)
{
	double	margin;

	margin = 0.2;
	if (data->map.grid[(int)(y - margin)][(int)(x - margin)] == '1')
		return (0);
	if (data->map.grid[(int)(y - margin)][(int)(x + margin)] == '1')
		return (0);
	if (data->map.grid[(int)(y + margin)][(int)(x - margin)] == '1')
		return (0);
	if (data->map.grid[(int)(y + margin)][(int)(x + margin)] == '1')
		return (0);
	return (1);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y
		* sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos_rot - data->player.plane_y
		* sin_rot;
	data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y
		* cos_rot;
	request_redraw(data);
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos_rot - data->player.dir_y
		* sin_rot;
	data->player.dir_y = old_dir_x * sin_rot + data->player.dir_y * cos_rot;
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos_rot - data->player.plane_y
		* sin_rot;
	data->player.plane_y = old_plane_x * sin_rot + data->player.plane_y
		* cos_rot;
	request_redraw(data);
}
