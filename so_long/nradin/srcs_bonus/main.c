/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:30:46 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 14:33:18 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int main(int argc, char *argv[]) {
    t_game *game;

    game = ft_calloc(sizeof(t_game), 1);
    if (argc != 2)
        throw_error(game, NULL, ARGS_ERROR);
    game->map = read_map(game, argv[1]);
    check_map(game);
    game_init(game);
    game->mlx = mlx_init(game->map_x * 60, game->map_y * 60, "Game", NULL);
    if (!game->mlx)
        throw_error(game, NULL, MLX_INIT_ERROR);
    init_images(game);
    init_enemies(game);
    mlx_close_hook(game->mlx, close_game, game);
    render_map(game, game->map);
    mlx_image_to_window(game->mlx, game->draw_buffer.img, 0, 0);
    mlx_key_hook(game->mlx, key_hook, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    return (0);
}