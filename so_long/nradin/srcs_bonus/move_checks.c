/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:44:29 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 12:02:30 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void moves_ifs(int key, int *x, int *y, t_being *being) {
    if (key == MLX_KEY_W || key == 3) {
        *y -= 1;
        being->offset_y = 5;
    } else if (key == MLX_KEY_S) {
        *y += 1;
        being->offset_y = -5;
    } else if (key == MLX_KEY_A) {
        *x -= 1;
        being->offset_x = 5;
    } else if (key == MLX_KEY_D) {
        *x += 1;
        being->offset_x = -5;
    }
}

int	check_win(t_game *game)
{
	t_comp	*comps;

	comps = calloc(1, sizeof(t_comp));
	count_components(game, game->map, comps);
	if (comps->collect == 0)
	{
		free(comps);
		return (1);
	}
	free(comps);
	return (0);
}

int	check_player(t_game *game, int x, int y)
{
	if (x == game->player_status.x - \
		game->player_status.offset_x / 4)
	{
		if (y == game->player_status.y - \
			game->player_status.offset_y / 4)
			return (1);
	}
	return (0);
}

int	check_enemies(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (x == game->enemy_status[i].x - \
			game->enemy_status[i].offset_x / 4)
		{
			if (y == game->enemy_status[i].y - \
				game->enemy_status[i].offset_y / 4)
				return (1);
		}
		i++;
	}
	return (0);
}

void	check_interaction(t_game *game, t_being	being)
{
	int	x;
	int	y;

	x = being.x;
	y = being.y;
	if (game->map[y][x] == COLLECTIBLE)
		game->map[y][x] = FLOOR;
	if (check_enemies(game, x, y))
	{
		game->win_condition = -1;
		return ;
	}
	if (game->map[y][x] == MAP_EXIT)
	{
		if (check_win(game))
			game->win_condition = 1;
	}
}
