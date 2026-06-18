/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:59:27 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 10:34:31 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
close game on esc
*/
int	close_game(t_game *game)
{
	game_over(game);
	return (0);
}

/*
key hooks for the game
*/
int	key_hook(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		game_over(game);
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		game->player_direction = 2;
		move_player(game, 0, -1);
	}
	if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		game->player_direction = 3;
		move_player(game, 0, 1);
	}
	if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		game->player_direction = 1;
		move_player(game, -1, 0);
	}
	if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		game->player_direction = 0;
		move_player(game, 1, 0);
	}
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 17, 0L, close_game, game);
}
