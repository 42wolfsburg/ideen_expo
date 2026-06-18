/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:50:53 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 22:40:59 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	check_player_count(int count)
{
	if (count != 1)
	{
		printf("Error: Found %d players, expected exactly 1\n", count);
		return (0);
	}
	return (1);
}

void	set_east_west_direction(t_game *game, char dir)
{
	if (dir == 'E')
	{
		game->player.playdir_x = 1;
		game->player.playdir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.playdir_x = -1;
		game->player.playdir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	set_player_direction(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.playdir_x = 0;
		game->player.playdir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		game->player.playdir_x = 0;
		game->player.playdir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else
		set_east_west_direction(game, dir);
}

void	warn_high_resolution(int w, int h)
{
	if (w >= 3840 || h >= 2160)
	{
		printf("\n╔═══════════════════════════════════════════════╗\n");
		printf("║            ⚠️  PERFORMANCE WARNING ⚠️           ║\n");
		printf("╠═══════════════════════════════════════════════╣\n");
		printf("║     4K resolution selected: % dx %d       ║\n", w, h);
		printf("║     Raycasting will be VERY slow!             ║\n");
		printf("║     Expect severe lag and low FPS.            ║\n");
		printf("║                                               ║\n");
		printf("║     Continue anyway? (y/n):                   ║\n");
		printf("╠═══════════════════════════════════════════════╣\n");
	}
	else if (w >= 2560 || h >= 1440)
	{
		printf("\nNote: %d x %d may impact performance on some systems\n",
			w, h);
		printf("Continue? (y/n): ");
	}
}
