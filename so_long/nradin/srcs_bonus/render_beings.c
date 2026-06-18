/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_beings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:09:55 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 12:50:31 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	calc_off(int offset)
{
	if (offset > 0)
	{
		return (-4 + offset);
	}
	else if (offset < 0)
	{
		return (4 + offset);
	}
	return (0);
}

int	check_direction(t_being *being)
{
	if (being->offset_x < 0)
		being->last_move = 2;
	else if (being->offset_x > 0)
		being->last_move = 0;
	else if (being->offset_y > 0)
		being->last_move = 3;
	else if (being->offset_y < 0)
		being->last_move = 1;
	return (being->last_move);
}

int	check_move(int *offset, int *coord)
{
	if ((*offset) > 0)
	{
		(*offset)--;
		if ((*offset) == 0)
		{
			(*coord)--;
			return (1);
		}
	}
	else if ((*offset) < 0)
	{
		(*offset)++;
		if ((*offset) == 0)
		{
			(*coord)++;
			return (1);
		}
	}
	return (0);
}

void render_animations(t_game *game) {
    int i;

    // redraw_backgroung(game);
	render_map(game, game->map);
    render_exit(game);
    render_coins(game);
    
    i = 0;
    while (i < game->enemy_count) {
        if (!(game->win_condition && game->map[game->enemy_status[i].y]
              [game->enemy_status[i].x] == MAP_EXIT))
            render_enemy(game, &game->enemy_status[i]);
        i++;
    }
	if (game->win_condition) {
        if (game->win_condition == -1)
            render_player_loose(game);
        else
            render_player_win(game);
    } else
        render_player(game, &game->player_status);
}
