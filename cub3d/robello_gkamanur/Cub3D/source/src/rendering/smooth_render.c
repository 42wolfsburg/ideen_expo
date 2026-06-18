/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:12:19 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:05:29 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rendering.h"

void	request_redraw(t_data *data)
{
	data->needs_redraw = 1;
}

int	needs_redraw(t_data *data)
{
	return (data->needs_redraw);
}

void	clear_redraw_flag(t_data *data)
{
	data->needs_redraw = 0;
}

int	smooth_render_loop(t_data *data)
{
	if (needs_redraw(data))
	{
		render_frame(data);
		clear_redraw_flag(data);
	}
	else
	{
		usleep(1000);
	}
	return (0);
}
