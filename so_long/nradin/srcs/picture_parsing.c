/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:02:57 by nradin            #+#    #+#             */
/*   Updated: 2023/03/03 13:42:34 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

t_image	read_xmp_image(void *mlx, char *file, t_game *game)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, file, &sprite.x, &sprite.y);
	if (sprite.xpm_ptr == NULL)
		throw_error(game, NULL, SPRITE_ERROR);
	return (sprite);
}

int	init_images(t_game	*game)
{
	if (!game)
		return (0);
	game->wall = read_xmp_image(game->mlx, WALL_PATH, game);
	game->player = read_xmp_image(game->mlx, PLAYER_PATH, game);
	game->player_win = read_xmp_image(game->mlx, PLAYER_WIN_PATH, game);
	game->floor = read_xmp_image(game->mlx, FLOOR_PATH, game);
	game->map_exit = read_xmp_image(game->mlx, MAP_EXIT_PATH, game);
	game->collectible = read_xmp_image(game->mlx, COLLECTIBLE_PATH, game);
	return (1);
}
