/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:47:08 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 12:51:14 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

// void render_player(t_game *game, t_being *player) {
//     int moved;

//     moved = check_move(&player->offset_x, &player->x);
//     if (!moved)
//         moved = check_move(&player->offset_y, &player->y);
//     if (moved)
//         check_interaction(game, *player);
//     if (game->map[player->y][player->x] != MAP_EXIT)
//         render_image(game,
//                      game->shadow,
//                      player->x * 60 +
//                      calc_off(player->offset_x) * 15,
//                      player->y * 60 +
//                      calc_off(player->offset_y) * 15);
//     render_image(game,
//                  game->player[check_direction(player)]
//                  [ft_abs(calc_off(player->offset_x)) +
//                   ft_abs(calc_off(player->offset_y))],
//                  player->x * 60 +
//                  calc_off(player->offset_x) * 15,
//                  player->y * 60 +
//                  calc_off(player->offset_y) * 15);
// }
// void render_player(t_game *game, t_being *player) {
//     int moved;
//     int shadow_x;
//     int shadow_y;
//     int player_x;
//     int player_y;

//     moved = check_move(&player->offset_x, &player->x);
//     if (!moved)
//         moved = check_move(&player->offset_y, &player->y);
//     if (moved)
//         check_interaction(game, *player);

//     shadow_x = player->x * 60 + calc_off(player->offset_x) * 15;
//     shadow_y = player->y * 60 + calc_off(player->offset_y) * 15;
//     player_x = player->x * 60 + calc_off(player->offset_x) * 15;
//     player_y = player->y * 60 + calc_off(player->offset_y) * 15;

//     // Переміщення тіні
//     if (game->shadow.img && game->shadow.img->instances) {
//         game->shadow.img->instances[0].x = shadow_x;
//         game->shadow.img->instances[0].y = shadow_y;
//     } else if (game->shadow.img) {
//         // Якщо тінь ще не була додана до вікна
//         mlx_image_to_window(game->mlx, game->shadow.img, shadow_x, shadow_y);
//     }

//     // Переміщення гравця
//     if (game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))].img &&
//         game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))].img->instances) {
//             // redraw_being_backgroung(game, &game->player_status);
//         game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))].img->instances[0].x = player_x;
//         game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))].img->instances[0].y = player_y;
//     } else if (game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))].img) {
//         // Якщо гравець ще не був доданий до вікна
//         mlx_image_to_window(game->mlx, game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))].img, player_x, player_y);
//     }
// }
void render_player(t_game *game, t_being *player) {
    int moved;
    int shadow_x;
    int shadow_y;
    int player_x;
    int player_y;
    moved = check_move(&player->offset_x, &player->x);
    if (!moved)
        moved = check_move(&player->offset_y, &player->y);
    if (moved)
        check_interaction(game, *player);

    shadow_x = player->x * 60 + calc_off(player->offset_x) * 15;
    shadow_y = player->y * 60 + calc_off(player->offset_y) * 15;
    player_x = player->x * 60 + calc_off(player->offset_x) * 15;
    player_y = player->y * 60 + calc_off(player->offset_y) * 15;

    // Малювання тіні
    render_image(game, game->shadow, shadow_x, shadow_y);

    // Малювання гравця
    render_image(game, game->player[check_direction(player)][ft_abs(calc_off(player->offset_x)) + ft_abs(calc_off(player->offset_y))], player_x, player_y);
}

void render_player_loose(t_game *game) {
    int i;
    int j;

    i = 0;
    while (game->map[i]) {
        j = 0;
        while (game->map[i][j] && game->map[i][j] != '\n') {
            if (game->map[i][j] == MAP_EXIT) {
                render_image(game, game->floor, j * 60, i * 60);
                render_image(game, game->player_loose, j * 60, i * 60);
            }
            j++;
        }
        i++;
    }
}

void render_player_win(t_game *game) {
    render_image(game, game->player_win,
                 game->player_status.x * 60, game->player_status.y * 60);
}