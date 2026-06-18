/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unreachable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:46:46 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:49:33 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_unreachable_entity(char c)
{
	return (c == 'T' || c == '0' || c == 'C' || c == 'X' || c == 'D');
}

int	check_unreachable_entities(char **map, char **reachable, int dims[2])
{
	int	i;
	int	j;

	print_reachable_map_debug(map, reachable, dims);
	i = 0;
	while (i < dims[0])
	{
		j = 0;
		while (j < dims[1])
		{
			if (is_unreachable_entity(map[i][j]) && reachable[i][j] != 'R')
			{
				print_unreachable_error(i, j, map[i][j]);
				return (0);
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return (1);
}

void	finalize_map_processing(t_game *game, char **padded, char **processed)
{
	game->map.map = processed;
	free_strings(padded);
	free_strings(game->map.raw_map);
	game->map.raw_map = NULL;
	game->player.play_x = game->player.raw_x + 0.5;
	game->player.play_y = game->player.raw_y + 0.5;
	set_player_direction(game, game->player.start_char);
}

void	flood_fill(char **map, int pos[2], char fill_char, char target_char)
{
	int	dims[2];
	int	new_pos[2];

	if (!map || !map[0])
		return ;
	dims[0] = 0;
	while (map[dims[0]])
		dims[0] = dims[0] + 1;
	dims[1] = ft_strlen(map[0]);
	if (pos[0] < 0 || pos[0] >= dims[0] || pos[1] < 0 || pos[1] >= dims[1])
		return ;
	if (map[pos[0]][pos[1]] != target_char)
		return ;
	map[pos[0]][pos[1]] = fill_char;
	new_pos[0] = pos[0] - 1;
	new_pos[1] = pos[1];
	flood_fill(map, new_pos, fill_char, target_char);
	new_pos[0] = pos[0] + 1;
	flood_fill(map, new_pos, fill_char, target_char);
	new_pos[0] = pos[0];
	new_pos[1] = pos[1] - 1;
	flood_fill(map, new_pos, fill_char, target_char);
	new_pos[1] = pos[1] + 1;
	flood_fill(map, new_pos, fill_char, target_char);
}

void	flood_fill_walkable(char **map, int pos[2], char fill_char, int dims[2])
{
	char	c;
	int		new_pos[2];

	if (pos[0] < 0 || pos[0] >= dims[0] || pos[1] < 0 || pos[1] >= dims[1])
		return ;
	c = map[pos[0]][pos[1]];
	if ((c == 'T' || c == '0' || c == 'N' || c == 'S' || c == 'E'
			|| c == 'W' || c == 'C' || c == 'X' || c == 'D') && c != fill_char)
	{
		map[pos[0]][pos[1]] = fill_char;
		new_pos[0] = pos[0] - 1;
		new_pos[1] = pos[1];
		flood_fill_walkable(map, new_pos, fill_char, dims);
		new_pos[0] = pos[0] + 1;
		flood_fill_walkable(map, new_pos, fill_char, dims);
		new_pos[0] = pos[0];
		new_pos[1] = pos[1] - 1;
		flood_fill_walkable(map, new_pos, fill_char, dims);
		new_pos[1] = pos[1] + 1;
		flood_fill_walkable(map, new_pos, fill_char, dims);
	}
}
