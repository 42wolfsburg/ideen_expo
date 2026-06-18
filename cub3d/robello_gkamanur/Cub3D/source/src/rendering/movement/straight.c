/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:15:52 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:04:24 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_y * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	request_redraw(data);
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_y * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	request_redraw(data);
}

void	strafe_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x - data->player.dir_y * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_x * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	request_redraw(data);
}

void	strafe_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_y * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_x * MOVE_SPEED;
	if (is_valid_position(data, new_x, data->player.y))
		data->player.x = new_x;
	if (is_valid_position(data, data->player.x, new_y))
		data->player.y = new_y;
	request_redraw(data);
}
