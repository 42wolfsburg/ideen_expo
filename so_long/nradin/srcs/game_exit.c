/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:06:08 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 14:01:52 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_game(t_game *game)
{
	if (game->map)
		ft_strstr_free(game->map);
	if (game->wall.xpm_ptr)
		mlx_destroy_image(game->mlx, game->wall.xpm_ptr);
	if (game->player.xpm_ptr)
		mlx_destroy_image(game->mlx, game->player.xpm_ptr);
	if (game->floor.xpm_ptr)
		mlx_destroy_image(game->mlx, game->floor.xpm_ptr);
	if (game->map_exit.xpm_ptr)
		mlx_destroy_image(game->mlx, game->map_exit.xpm_ptr);
	if (game->collectible.xpm_ptr)
		mlx_destroy_image(game->mlx, game->collectible.xpm_ptr);
	if (game->player_win.xpm_ptr)
		mlx_destroy_image(game->mlx, game->player_win.xpm_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free(game);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit (0);
	return (0);
}
