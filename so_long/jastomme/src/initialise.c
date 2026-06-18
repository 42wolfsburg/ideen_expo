/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:59:36 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 10:39:01 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
define textures for	wall(1), ground(0), player(P), collectibles(C),
exit(E) open and closed
*/
void	init_textures(t_game *game)
{
	int	i;
	int	width;
	int	height;

	game->img[0] = mlx_xpm_file_to_image(game->mlx, TXT_P, &width, &height);
	game->img[1] = mlx_xpm_file_to_image(game->mlx, TXT_C, &width, &height);
	game->img[2] = mlx_xpm_file_to_image(game->mlx, TXT_EX_O, &width, &height);
	game->img[3] = mlx_xpm_file_to_image(game->mlx, TXT_GRD, &width, &height);
	game->img[4] = mlx_xpm_file_to_image(game->mlx, TXT_WALL, &width, &height);
	game->img[5] = mlx_xpm_file_to_image(game->mlx, TXT_EX_C, &width, &height);
	i = 0;
	while (i < 6)
	{
		if (!game->img[i])
			exit_game(game, "ERROR: texture init");
		i++;
	}
}

/*
render map
*/
void	render_map(t_game *game)
{
	int		x;
	int		y;
	int		window_x;
	int		window_y;
	t_map	*temp;

	temp = game->map;
	y = 0;
	while (temp != NULL)
	{
		x = 0;
		while (temp->line[x] != '\0')
		{
			window_x = x * TILE_SIZE;
			window_y = y * TILE_SIZE;
			render_textures(temp->line[x], game, window_x, window_y);
			x++;
		}
		y++;
		temp = temp->next;
	}
}

/*
initialises window, map, mlx, textures, map rendering, key setup and mlx loop.
*/
void	init_window(t_game *game)
{
	size_t	win_width;
	size_t	win_height;
	size_t	map_width;
	size_t	map_height;

	get_map_dimensions(game->map, &map_width, &map_height);
	win_width = TILE_SIZE * map_width;
	win_height = TILE_SIZE * map_height;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		exit_game(game, "ERROR: mlx init");
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (!game->win)
		exit_game(game, "ERROR: win init");
	init_textures(game);
	render_map(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
}

/*
put textures to window with mlx
*/
void	render_textures(char target, t_game *game, int x, int y)
{
	if (target == '1')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img[4], x, y);
	}
	else if (target == '0')
		mlx_put_image_to_window(game->mlx, game->win, game->img[3], x, y);
	else if (target == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->img[0], x, y);
	else if (target == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img[1], x, y);
	else if (target == 'E')
	{
		if (game->collected == game->c_count)
			mlx_put_image_to_window(game->mlx, game->win, game->img[2], x, y);
		else
			mlx_put_image_to_window(game->mlx, game->win, game->img[5], x, y);
	}
}

void	init_values(t_game *game)
{
	game->collected = 0;
	game->player_direction = 0;
	game->steps = 0;
}
