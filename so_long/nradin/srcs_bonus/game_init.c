/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:22:34 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 15:02:47 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	game_init(t_game *game)
{
	game->map_x = ft_strlen(game->map[0]) - 1;
	game->map_y = ft_strstr_len(game->map);
	game->player_status.offset_x = 0;
	game->player_status.offset_y = 0;
	game->player_status.last_move = 1;
}
