/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <<robello-@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:08:30 by robello-          #+#    #+#             */
/*   Updated: 2025/12/20 19:08:30 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.keys &= ~FWRD;
	else if (keycode == KEY_S)
		game->input.keys &= ~BWRD;
	else if (keycode == KEY_A)
		game->input.keys &= ~LEFT;
	else if (keycode == KEY_D)
		game->input.keys &= ~RIGHT;
	else if (keycode == KEY_LEFT)
		game->input.keys &= ~TURN_L;
	else if (keycode == KEY_RIGHT)
		game->input.keys &= ~TURN_R;
	else if (keycode == KEY_SPACE)
		game->input.keys &= ~(1 << 6);
	return (0);
}

void	ft_rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.playdir_x;
	game->player.playdir_x = game->player.playdir_x * cos(rot_speed)
		- game->player.playdir_y * sin(rot_speed);
	game->player.playdir_y = old_dir_x * sin(rot_speed)
		+ game->player.playdir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	double		rot_speed;
	int			delta_x;

	(void)y;
	if (!game->bonus.s_mouse.enabled)
	{
		last_x = -1;
		return (0);
	}
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	rot_speed = delta_x * game->bonus.s_mouse.sensitivity;
	ft_rotate_player(game, rot_speed);
	mlx_mouse_move(game->mlx, game->window, game->win_w / 2, game->win_h / 2);
	last_x = game->win_w / 2;
	return (0);
}

void	ft_setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->window, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->window, 17, 0, handle_window_close, game);
	mlx_hook(game->window, 6, 1L << 6, handle_mouse_move, game);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_mouse_move(game->mlx, game->window, game->win_w / 2, game->win_h / 2);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	create_game_window(t_game *game)
{
	game->window = mlx_new_window(game->mlx, game->win_w,
			game->win_h, "##*-- MAD LAB3D -- *##");
	if (!game->window)
	{
		write(2, "Error: Window creation failed\n", 30);
		return (0);
	}
	game->frame.img.img = mlx_new_image(game->mlx,
			game->win_w, game->win_h);
	if (!game->frame.img.img)
	{
		write(2, "Error: Image creation failed\n", 29);
		return (0);
	}
	game->frame.img.addr = mlx_get_data_addr(game->frame.img.img,
			&game->frame.img.bpp, &game->frame.img.linen,
			&game->frame.img.endian);
	game->frame.img.width = game->win_w;
	game->frame.img.height = game->win_h;
	mlx_hook(game->window, 17, 0, handle_window_close, game);
	return (1);
}
