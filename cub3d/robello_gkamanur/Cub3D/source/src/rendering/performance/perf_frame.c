/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:18:13 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 20:33:07 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

void	update_fps(t_data *data)
{
	double	current_time;

	current_time = get_time();
	data->timing.frame_count++;
	if (current_time - data->timing.fps_timer >= 1.0)
	{
		data->timing.fps = data->timing.frame_count / (current_time
				- data->timing.fps_timer);
		data->timing.frame_count = 0;
		data->timing.fps_timer = current_time;
	}
}

void	limit_framerate(t_data *data, int target_fps)
{
	double	current_time;
	double	target_frame_time;
	double	sleep_time;

	current_time = get_time();
	target_frame_time = 1.0 / target_fps;
	if (data->timing.last_frame_time > 0)
	{
		sleep_time = target_frame_time - (current_time
				- data->timing.last_frame_time);
		if (sleep_time > 0)
			usleep((int)(sleep_time * 1000000));
	}
	data->timing.last_frame_time = get_time();
}
