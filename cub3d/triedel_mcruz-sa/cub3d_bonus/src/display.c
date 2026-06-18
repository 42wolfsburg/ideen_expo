/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:53:15 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 19:53:04 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <mlx.h>

void	display_init(t_display *disp, int w, int h)
{
	disp->mlx = mlx_init();
	disp->win = mlx_new_window(disp->mlx, w, h, DISPLAY_TITLE);
	disp->width = w;
	disp->height = h;
	img_init(&disp->buffer, disp->mlx, disp->width, disp->height);
}

void	display_deinit(t_display *disp)
{
	img_deinit(&disp->buffer, disp->mlx);
	mlx_destroy_window(disp->mlx, disp->win);
	mlx_destroy_display(disp->mlx);
	free(disp->mlx);
}

void	display_update(t_display *disp)
{
	mlx_put_image_to_window(disp->mlx, disp->win, disp->buffer.mlximg, 0, 0);
}
