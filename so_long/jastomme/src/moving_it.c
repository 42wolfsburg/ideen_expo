/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:58:35 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/05 14:47:44 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*get_target_pos(t_map *map, int target_y)
{
	int		i;
	t_map	*temp;

	i = 0;
	temp = map;
	while (i < target_y)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

void	player_events(t_game *game, char target_tile)
{
	if (target_tile == 'C')
		game->collected++;
	else if (target_tile == 'E' && game->collected == game->c_count)
	{
		you_won(game);
		exit_game(game, "");
	}
	else if (target_tile == 'E' && game->collected != game->c_count)
		no_exit();
}

void	update_p_pos(t_game *game, t_map *old_pos, int new_x, int new_y)
{
	old_pos->line[game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
}

void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	t_map	*temp;
	t_map	*old_pos;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	temp = get_target_pos(game->map, new_y);
	if (temp->line[new_x] != '1')
	{
		old_pos = get_target_pos(game->map, game->player_y);
		player_events(game, temp->line[new_x]);
		if (temp->line[new_x] == 'E' && game->collected != game->c_count)
			return ;
		update_p_pos(game, old_pos, new_x, new_y);
		temp->line[game->player_x] = 'P';
		game->steps++;
		ft_printf("Steps taken: %d\n", game->steps);
		render_map(game);
		render_steps(game);
	}
}
