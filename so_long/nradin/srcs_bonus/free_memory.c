/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:23:20 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 14:01:57 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void free_exit_sprites(t_game *game) {
    if (!game)
        return;
    for (int i = 0; i < 5; i++) {
        if (game->map_exit[i].img)
            mlx_delete_image(game->mlx, game->map_exit[i].img);
    }
}

void free_player_sprites(t_game *game) {
    if (!game)
        return;
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 5; k++) {
            if (game->player[j][k].img && k != 2 && k != 4)
                mlx_delete_image(game->mlx, game->player[j][k].img);
        }
    }
}

void free_enemy_sprites(t_game *game) {
    if (!game)
        return;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                if (game->enemy[i][j][k].img && k != 2 && k != 4)
                    mlx_delete_image(game->mlx, game->enemy[i][j][k].img);
            }
        }
    }
}

void free_other_sprites(t_game *game) {
    if (!game)
        return;
    if (game->wall.img)
        mlx_delete_image(game->mlx, game->wall.img);
    if (game->floor.img)
        mlx_delete_image(game->mlx, game->floor.img);
    if (game->collectible.img)
        mlx_delete_image(game->mlx, game->collectible.img);
    if (game->player_win.img)
        mlx_delete_image(game->mlx, game->player_win.img);
    if (game->player_loose.img)
        mlx_delete_image(game->mlx, game->player_loose.img);
    if (game->shadow.img)
        mlx_delete_image(game->mlx, game->shadow.img);
    if (game->shadow_coin.img)
        mlx_delete_image(game->mlx, game->shadow_coin.img);
    if (game->black.img)
        mlx_delete_image(game->mlx, game->black.img);
}

void free_game(t_game *game) {
    if (game->map)
        ft_strstr_free(game->map);
    free_enemy_sprites(game);
    free_player_sprites(game);
    free_exit_sprites(game);
    free_other_sprites(game);
    free(game->enemy_status);
    if (game->mlx)
        mlx_terminate(game->mlx);
    free(game);
}