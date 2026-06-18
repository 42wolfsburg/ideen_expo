/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:57:47 by nradin            #+#    #+#             */
/*   Updated: 2023/03/01 13:24:13 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void render_exit(t_game *game) {
    int i;
    int j;

    i = 0;
    while (game->map[i]) {
        j = 0;
        while (game->map[i][j] && game->map[i][j] != '\n') {
            if (game->map[i][j] == MAP_EXIT) {
                render_image(game, game->floor, j * 60, i * 60);
                if (!check_win(game))
                    render_image(game, game->map_exit[0], j * 60, i * 60);
                else
                    render_image(game, game->map_exit[game->frame % 4 + 1],
                                 j * 60, i * 60);
            }
            j++;
        }
        i++;
    }
}

int calc_coin_pos(int frame) {
    if (frame == 0 || frame == 6)
        return (0);
    if (frame == 1 || frame == 5)
        return (1);
    if (frame == 2 || frame == 4)
        return (2);
    if (frame == 3)
        return (3);
    if (frame == 7 || frame == 11)
        return (-1);
    if (frame == 8 || frame == 10)
        return (-2);
    return (-3);
}

void render_coins(t_game *game) {
    int i;
    int j;

    i = 0;
    while (game->map[i]) {
        j = 0;
        while (game->map[i][j] && game->map[i][j] != '\n') {
            if (game->map[i][j] == COLLECTIBLE) {
                render_image(game, game->shadow_coin,
                             j * 60, i * 60 + calc_coin_pos(game->frame));
                render_image(game, game->collectible,
                             j * 60, i * 60 + calc_coin_pos(game->frame));
            }
            j++;
        }
        i++;
    }
}