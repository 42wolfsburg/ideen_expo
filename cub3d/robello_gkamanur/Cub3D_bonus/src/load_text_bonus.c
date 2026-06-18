/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:58:55 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:59:20 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_img	load_tx(void *mlx, char *path)
{
	t_img	img;
	int		width;
	int		height;
	char	*trimmed;

	trimmed = ft_strtrim(path, "\r\n ");
	if (!trimmed)
		return ((t_img){0});
	img.img = mlx_xpm_file_to_image(mlx, trimmed, &width, &height);
	if (!img.img)
	{
		write(2, "Error: Failed to load texture: ", 31);
		write(2, trimmed, ft_strlen(trimmed));
		write(2, "\n", 1);
		img.addr = NULL;
		img.width = 0;
		img.height = 0;
		free(trimmed);
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linen, &img.endian);
	img.width = width;
	img.height = height;
	free(trimmed);
	return (img);
}

int	load_game_over_win_textures(t_game *game)
{
	printf("\nLoading Final Textures (choice %d)...\n", game->res_choice);
	printf("  Please wait for a brief moment :) ...\n");
	if (game->res_choice >= 5)
	{
		game->tex.tex[G_OVER] = load_tx(game->mlx, "textures/game_over3.xpm");
		game->tex.tex[Y_WIN] = load_tx(game->mlx, "textures/game_win3.xpm");
	}
	else if (game->res_choice >= 3)
	{
		game->tex.tex[G_OVER] = load_tx(game->mlx, "textures/game_over2.xpm");
		game->tex.tex[Y_WIN] = load_tx(game->mlx, "textures/game_win2.xpm");
	}
	else
	{
		game->tex.tex[G_OVER] = load_tx(game->mlx, "./textures/game_over1.xpm");
		game->tex.tex[Y_WIN] = load_tx(game->mlx, "./textures/game_win1.xpm");
	}
	if (!game->tex.tex[G_OVER].img || !game->tex.tex[Y_WIN].img)
		return (printf("Error: Failed to load game over/win textures\n"), 0);
	printf("  ✓ Game over/win textures loaded\n");
	return (1);
}

int	load_single_collectible_texture(t_game *game, int i)
{
	char	path[50];

	snprintf(path, sizeof(path), "textures/chili_%d.xpm", i);
	game->tex.tex[COLL_0 + i] = load_tx(game->mlx, path);
	if (!game->tex.tex[COLL_0 + i].img)
	{
		printf("Warning: Could not load collectible frame %d @'%s'\n", i, path);
		snprintf(path, sizeof(path), "./textures/collectible_%d.xpm", i);
		game->tex.tex[COLL_0 + i] = load_tx(game->mlx, path);
	}
	if (game->tex.tex[COLL_0 + i].img)
		printf("  ✓ Collectible frame %d loaded\n", i);
	return (1);
}

int	load_collectible_textures(t_game *game)
{
	int	i;

	printf("\nLoading collectible textures...\n");
	i = 0;
	while (i < COLL_FRAME)
	{
		if (!load_single_collectible_texture(game, i))
			return (0);
		i = i + 1;
	}
	return (1);
}

int	load_single_enemy_texture(t_game *game, int i)
{
	char	path[50];

	snprintf(path, sizeof(path), "textures/ene_%d.xpm", i);
	game->tex.tex[ENEMY_0 + i] = load_tx(game->mlx, path);
	if (!game->tex.tex[ENEMY_0 + i].img)
	{
		printf("Warning: Could not load enemy frame %d at '%s'\n", i, path);
		snprintf(path, sizeof(path), "./textures/ene_%d.xpm", i);
		game->tex.tex[ENEMY_0 + i] = load_tx(game->mlx, path);
	}
	if (game->tex.tex[ENEMY_0 + i].img)
		printf("  ✓ Enemy frame %d loaded\n", i);
	return (1);
}
