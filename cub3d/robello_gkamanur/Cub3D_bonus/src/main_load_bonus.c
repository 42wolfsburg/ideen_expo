/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:00:47 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 19:02:53 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	debug_texture_loading(t_game *game)
{
	printf("\nLoading Wall textures...\n");
	if (game->tex.tex[WALL_N].img)
		printf("  ✓ WALL: N loaded\n");
	else
		printf("  ✗ WALL: N is missing\n");
	if (game->tex.tex[WALL_S].img)
		printf("  ✓ WALL: S loaded\n");
	else
		printf("  ✗ WALL: S is missing\n");
	if (game->tex.tex[WALL_E].img)
		printf("  ✓ WALL: E loaded\n");
	else
		printf("  ✗ WALL: E is missing\n");
	if (game->tex.tex[WALL_W].img)
		printf("  ✓ WALL: W loaded\n");
	else
		printf("  ✗ WALL: W is missing\n");
}

int	setup_bonus_entities(t_game *game)
{
	if (!allocate_bonus_entities(game))
	{
		printf("╔═════════════════════════════════════════════════════════╗\n");
		printf("║ Error:  Memory allocation failed for bonus entities     ║\n");
		printf("╚═════════════════════════════════════════════════════════╝\n");
		return (0);
	}
	fill_bonus_entities(game);
	printf("  ✓ Bonus entities allocated: %d doors (%d secret), ",
		game->doors.count, game->doors.secret_cnt);
	printf("%d collectibles, %d enemies\n",
		game->colls.total, game->enemies.ene_count);
	return (1);
}

int	load_enemy_textures(t_game *game)
{
	int	i;

	printf("\nLoading enemy textures...\n");
	i = 0;
	while (i < ENE_FRAME)
	{
		if (!load_single_enemy_texture(game, i))
			return (0);
		i = i + 1;
	}
	return (1);
}

int	load_door_textures(t_game *game)
{
	printf("  Loading door texture...\n");
	game->tex.tex[T_DOOR] = load_tx(game->mlx, "textures/ganesh.xpm");
	if (!game->tex.tex[T_DOOR].img)
	{
		printf("Warning: Could not load door texture @'textures/ganesh.xpm'\n");
		printf("Trying alternative path...\n");
		game->tex.tex[T_DOOR] = load_tx(game->mlx, "./textures/ganesh.xpm");
	}
	if (game->tex.tex[T_DOOR].img)
		printf("  ✓ Door texture loaded\n");
	printf("\nLoading secret door texture...\n");
	game->tex.tex[T_SECRET_D] = load_tx(game->mlx, "textures/maya.xpm");
	if (!game->tex.tex[T_SECRET_D].img)
	{
		printf("Warning: Could not load secret door texture\n");
		printf("Trying alternative path...\n");
		game->tex.tex[T_SECRET_D] = load_tx(game->mlx, "./textures/maya.xpm");
	}
	if (game->tex.tex[T_SECRET_D].img)
		printf("  ✓ Secret door texture loaded\n");
	return (1);
}

int	main_load_bonus_textures(t_game *game)
{
	printf("\n======= LOADING BONUS TEXTURES =======\n");
	if (!load_door_textures(game))
		return (0);
	if (!load_enemy_textures(game))
		return (0);
	if (!load_collectible_textures(game))
		return (0);
	if (!load_game_over_win_textures(game))
		return (0);
	debug_texture_loading(game);
	printf("\n====== BONUS TEXTURES LOADED ======\n\n\n");
	return (1);
}
