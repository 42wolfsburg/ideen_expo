/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:45:50 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 12:46:38 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void redraw_being_backgroung(t_game *game, t_being *being) {
    int dir;
    int x;
    int y;

    dir = check_direction(being);
    x = being->x;
    y = being->y;
    pick_image(game->map[y][x], game, x, y);
    if (dir == 0)
        x++; // Виправлено напрямок
    else if (dir == 1)
        y++;
    else if (dir == 2)
        x--; // Виправлено напрямок
    else if (dir == 3)
        y--;
    pick_image(game->map[y][x], game, x, y);
}

void redraw_coins_backgroung(t_game *game) {
    int i;
    int j;

    i = 0;
    while (game->map[i]) {
        j = 0;
        while (game->map[i][j] && game->map[i][j] != '\n') {
            if (game->map[i][j] == COLLECTIBLE) {
                render_image(game, game->floor, j * 60, i * 60);
            }
            j++;
        }
        i++;
    }
}

void redraw_backgroung(t_game *game) {
    int i;

    i = 0;
    redraw_being_backgroung(game, &game->player_status);
    redraw_coins_backgroung(game);
    while (i < game->enemy_count) {
        redraw_being_backgroung(game, &game->enemy_status[i]);
        i++;
    }
}
