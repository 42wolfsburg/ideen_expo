/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:37:48 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:38:58 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	validate_player_and_entities_reachable(char **map, int player_pos[2])
{
	char	**reachable;
	int		dims[2];

	if (!map || !map[0])
		return (0);
	dims[0] = 0;
	while (map[dims[0]])
		dims[0] = dims[0] + 1;
	dims[1] = ft_strlen(map[0]);
	reachable = copy_map_for_flood_fill(map, dims[0]);
	if (!reachable)
		return (0);
	flood_fill_walkable(reachable, player_pos, 'R', dims);
	if (check_unreachable_entities(map, reachable, dims) == 0)
	{
		free_strings(reachable);
		return (0);
	}
	free_strings(reachable);
	return (1);
}

int	count_bonus_entities(t_game *game, char c, int x, int y)
{
	if (c == 'D')
		game->doors.count++;
	else if (c == 'T')
	{
		game->doors.count++;
		game->doors.secret_cnt++;
		if (game->doors.secret_cnt > 1)
		{
			printf("Error: Multiple secret doors ('T'). Only 1 is allowed.\n");
			printf("Duplicate secret door @map [%d,%d]\n", x, y);
			return (0);
		}
	}
	else if (c == 'C')
		game->colls.total++;
	else if (c == 'X')
		game->enemies.ene_count++;
	return (1);
}

int	validate_single_char(t_game *g, int val_data[4], char c, int *player_cnt)
{
	if (!is_map_char(c))
	{
		print_char_error(c, val_data[0], val_data[1]);
		return (0);
	}
	if (ft_strchr("NSEW", c))
	{
		*player_cnt = *player_cnt + 1;
		g->player.raw_x = val_data[1];
		g->player.raw_y = val_data[2];
		g->player.start_char = c;
		if (*player_cnt > 1)
		{
			printf("Error: Found multiple players. Exactly one allowed.\n");
			printf("Duplicate player at map coordinates [%d, %d] facing '%c'\n",
				val_data[2] + 1, val_data[1] + 1, c);
			return (0);
		}
	}
	return (count_bonus_entities(g, c, val_data[1], val_data[2]));
}

int	validate_all_chars(t_game *g, char *line, int line_data[3], int *player_cnt)
{
	int	i;
	int	val_data[3];

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		val_data[0] = line_data[0];
		val_data[1] = i;
		val_data[2] = line_data[1];
		if (!validate_single_char(g, val_data, line[i], player_cnt))
			return (0);
		i = i + 1;
	}
	return (1);
}

int	validate_entity_counts(t_game *game)
{
	if (game->doors.secret_cnt != 1)
	{
		if (game->doors.secret_cnt == 0)
			printf("Error: No secret door('T') found. Exactly one required.\n");
		else
			printf("Error: Found %d secret doors('T'). Exactly one required.\n",
				game->doors.secret_cnt);
		return (0);
	}
	if (game->colls.total < 1)
	{
		printf("Error: No collectibles ('C') found. At least one required.\n");
		return (0);
	}
	if (game->enemies.ene_count < 1)
	{
		printf("Error: No enemies ('X') found. At least one required.\n");
		return (0);
	}
	return (1);
}
