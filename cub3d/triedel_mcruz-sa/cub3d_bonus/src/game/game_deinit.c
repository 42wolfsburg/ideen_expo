/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_deinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:49:46 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 13:35:52 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <mlx.h>
#include <pthread.h>

void	game_deinit_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TXTMAX + 1 + game->map.txtcount - 4)
	{
		img_deinit(&game->textures[i], game->disp.mlx);
		i++;
	}
	free(game->textures);
}

/// Deinitialize game
void	game_deinit(t_game *game)
{
	mlx_do_key_autorepeaton(game->disp.mlx);
	if (game->map.height > 0)
		map_deinit(&game->map);
	img_deinit(&game->mattex, game->disp.mlx);
	game_deinit_textures(game);
	free(game->hit_buffer);
	free(game->mt.data);
	pthread_mutex_destroy(&game->mutex_render);
	display_deinit(&game->disp);
}

int	game_handle_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	game_setup_window_close_handler(void *win_ptr)
{
	mlx_hook(win_ptr, 17, 0, game_handle_close, NULL);
}
