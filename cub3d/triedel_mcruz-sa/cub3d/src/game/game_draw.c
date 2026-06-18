/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:43:43 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 14:08:07 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <pthread.h>

void	game_render_multi(t_game *game)
{
	int		i;

	game->next_col = 0;
	i = -1;
	while (++i < THREADS)
	{
		game->threadinfos[i] = (t_threadinfo){game, i};
		pthread_create(&game->threads[i], NULL, game_render_thread,
			(void *)&game->threadinfos[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(game->threads[i], NULL);
}

void	game_render(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->disp.width)
	{
		game_render_col(game, x, game->upscale);
		x += game->upscale;
	}
}

void	game_draw(t_game *game)
{
	if (game->state == S_INTRO)
		game_draw_intro(game);
	else
		game_draw_frame(game);
	display_update(&game->disp);
}
