/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perf_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:31:02 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:31:30 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rendering.h"

static void	copy_column(t_data *data, int src_x, int dst_x)
{
	int		y;
	char	*src_col;
	char	*dst_col;
	int		bpp;

	bpp = data->img.bits_per_pixel / 8;
	src_col = data->img.addr + (src_x * bpp);
	dst_col = data->img.addr + (dst_x * bpp);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		*(unsigned int *)(dst_col + y * data->img.line_length)
			= *(unsigned int *)(src_col + y * data->img.line_length);
		y++;
	}
}

void	duplicate_column(t_data *data, int src_x, int count)
{
	int	dup;

	dup = 1;
	while (dup < count && (src_x + dup) < WIN_WIDTH)
	{
		copy_column(data, src_x, src_x + dup);
		dup++;
	}
}
