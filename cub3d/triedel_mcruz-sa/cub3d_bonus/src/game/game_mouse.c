/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:22:15 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 18:22:17 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	game_mouse_trap(t_game *game)
{
	mlx_mouse_move(game->disp.mlx, game->disp.win, game->disp.width / 2,
		game->disp.height / 2);
	mlx_mouse_hide(game->disp.mlx, game->disp.win);
}

void	game_mouse_release(t_game *game)
{
	mlx_mouse_show(game->disp.mlx, game->disp.win);
}
