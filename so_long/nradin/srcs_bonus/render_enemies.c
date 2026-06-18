/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:57:24 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 15:03:12 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	enemy_ifs(t_being *enemy, char direct)
{
	if (direct == ENEMY_HORIZONTAL)
		enemy->last_move = rand() % 2 * 2;
	if (direct == ENEMY_VERTICAL)
		enemy->last_move = rand() % 2 * 2 + 1;
	enemy->type = rand() % 2;
}

void	add_enemies(t_game *game)
{
	int		i;
	int		j;
	int		e;

	srand(time(NULL));
	i = 0;
	e = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == ENEMY_HORIZONTAL || \
				game->map[i][j] == ENEMY_VERTICAL)
			{
				enemy_ifs(&game->enemy_status[e], game->map[i][j]);
				game->enemy_status[e].x = j;
				game->enemy_status[e].y = i;
				e++;
				game->map[i][j] = FLOOR;
			}
			j++;
		}
		i++;
	}
}

int	init_enemies(t_game *game)
{
	t_comp	*comps;

	comps = ft_calloc(sizeof(t_comp), 1);
	count_components(game, game->map, comps);
	game->enemy_count = comps->enemy;
	game->enemy_status = ft_calloc(sizeof(t_being), comps->enemy);
	add_enemies(game);
	free(comps);
	return (1);
}

void render_enemy(t_game *game, t_being *enemy) {
    int moved;

    moved = check_move(&enemy->offset_x, &enemy->x);
    if (!moved)
        moved = check_move(&enemy->offset_y, &enemy->y);
    if (moved)
        check_interaction(game, game->player_status);
    if (game->map[enemy->y][enemy->x] != MAP_EXIT)
        render_image(game,
                     game->shadow,
                     enemy->x * 60 +
                     calc_off(enemy->offset_x) * 15,
                     enemy->y * 60 +
                     calc_off(enemy->offset_y) * 15);
    render_image(game,
                 game->enemy[enemy->type]
                 [check_direction(enemy)]
                 [ft_abs(calc_off(enemy->offset_x)) +
                  ft_abs(calc_off(enemy->offset_y))],
                 enemy->x * 60 +
                 calc_off(enemy->offset_x) * 15,
                 enemy->y * 60 +
                 calc_off(enemy->offset_y) * 15);
}