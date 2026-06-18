/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:49:49 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/23 15:02:54 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

void	init_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = FOV_P;
	player->plane_y = 0;
}

void	init_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = FOV_N;
	player->plane_y = 0;
}

void	init_east(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = FOV_P;
}

void	init_west(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = FOV_N;
}

// void	init_north(t_player *player)
// {
// 	player->dir_x = 0;
// 	player->dir_y = -1;
// 	player->plane_x = 1.0;
// 	player->plane_y = 0;
// }

// void	init_south(t_player *player)
// {
// 	player->dir_x = 0;
// 	player->dir_y = 1;
// 	player->plane_x = -1.0;
// 	player->plane_y = 0;
// }

// void	init_east(t_player *player)
// {
// 	player->dir_x = 1;
// 	player->dir_y = 0;
// 	player->plane_x = 0;
// 	player->plane_y = 1.0;
// }

// void	init_west(t_player *player)
// {
// 	player->dir_x = -1;
// 	player->dir_y = 0;
// 	player->plane_x = 0;
// 	player->plane_y = -1.0;
// } 
void	init_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
		init_north(player);
	else if (direction == 'S')
		init_south(player);
	else if (direction == 'E')
		init_east(player);
	else if (direction == 'W')
		init_west(player);
}
