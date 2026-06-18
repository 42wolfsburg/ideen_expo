/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:06:08 by nradin            #+#    #+#             */
/*   Updated: 2023/03/03 17:20:54 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void close_game(void *param) {
	
    t_game *game = (t_game *)param;
    free_game(game);
    exit(EXIT_FAILURE);
}

void game_end(t_game *game) {
    int i;

    i = 0;
    game->player_status.last_move = 1;
    game->player_status.offset_x = 0;
    game->player_status.offset_y = 0;
    while (i < game->enemy_count) {
        game->enemy_status[i].last_move = 1;
        game->enemy_status[i].offset_x = 0;
        game->enemy_status[i].offset_y = 0;
        i++;
    }
    render_map(game, game->map);
    render_animations(game);
}