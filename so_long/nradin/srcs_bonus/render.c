/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:17:39 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 15:12:46 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void render_image(t_game *game, t_image sprite, int x, int y) {
    if (sprite.img) {
        // mlx_image_to_window(game->mlx, sprite.img, x, y);
        copy_image_to_buffer(game->draw_buffer.img, sprite.img, x, y);
    }
}
void pick_image(char comp, t_game *game, int x, int y) {
    render_image(game, game->floor, x * 60, y * 60);
    if (comp == WALL)
        render_image(game, game->wall, x * 60, y * 60);
}

void render_map(t_game *game, char **map) {
    int i;
    int j;

    i = 0;
    while (map[i]) {
        j = 0;
        while (map[i][j] && map[i][j] != '\n') {
            pick_image(map[i][j], game, j, i);
            j++;
        }
        i++;
    }
    // mlx_image_to_window(game->mlx, game->draw_buffer.img, 0, 0);
}

void render_frame(t_game *game, int *game_ended) {
    game->frame++;
    if (game->win_condition == 0) {
        if (game->frame == 12) {
            game->frame = 0;
            move_enemies(game);
        }
        clear_buffer(game->draw_buffer.img, 0xFF000000);
        render_animations(game);
        mlx_image_to_window(game->mlx, game->draw_buffer.img, 0, 0);
        mlx_image_t *temp = game->draw_buffer.img;
        game->draw_buffer.img = game->display_buffer.img;
        game->display_buffer.img = temp;
        // show_moves(game);
    } else {
        *game_ended = 1;
        game_end(game);
        mlx_image_to_window(game->mlx, game->draw_buffer.img, 0, 0);
    }
}

void game_loop(void *param) {
    t_game *game = (t_game *)param;
    long long now;
    long long diff;
    static int game_ended;

    now = millitimestamp();
    diff = now - game->time;
    if (diff > 100 && !game_ended) {
        game->time = now;
        render_frame(game, &game_ended);
    }
}