/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:03:50 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 10:09:51 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "display.h"

// float	from_deg(float deg)
// {
// 	return (deg / 180 * M_PI);
// }

// float	to_deg(float rad)
// {
// 	return (rad / M_PI * 180);
// }

// Make mlx_mouse_get_pos platform independent
#ifdef LINUX

void	xmlx_mouse_get_pos(void *mlx, void *win, int *x, int *y)
{
	mlx_mouse_get_pos(mlx, win, x, y);
}

void	xmlx_destroy(void *mlx)
{
	mlx_loop_end(mlx);
	mlx_destroy_display(mlx);
}

#else

void	xmlx_mouse_get_pos(void *mlx, void *win, int *x, int *y)
{
	mlx_mouse_get_pos(win, x, y);
	(void) mlx;
}

void	xmlx_destroy(void *mlx)
{
	(void *) mlx;
}

#endif