/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:10:22 by robello           #+#    #+#             */
/*   Updated: 2026/01/25 18:16:46 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	parse_and_validate_map(int fd, t_game *game, char *first_line, int line_num)
{
	printf("\n\n======= PARSING MAP =======\n");
	if (!parse_raw_map(game, fd, first_line, line_num))
		return (print_map_error("Invalid map format   "), 0);
	printf("  ✓ Raw map parsed (%d lines)\n\n", game->map.height);
	if (!validate_entity_counts(game))
		return (print_map_error("Entity validation failed"), 0);
	if (!process_and_validate_map(game))
		return (print_map_error("Map validation failed"), 0);
	printf("\n\n  ✓ Map processed and validated\n");
	return (1);
}

char	*find_first_map_line(int fd, int *line_num)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		*line_num = *line_num + 1;
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
			return (line);
	}
	return (NULL);
}

int	parse_raw_map(t_game *game, int fd, char *first_line, int start_line)
{
	int	player_cnt;
	int	current_line;

	player_cnt = 0;
	current_line = start_line;
	if (first_line
		&& !process_first_line(game, first_line, current_line, &player_cnt))
		return (0);
	while (1)
	{
		if (!first_line)
			break ;
		first_line = get_next_line(fd);
		if (!first_line)
			break ;
		current_line = current_line + 1;
		if (!process_next_line(game, first_line, current_line, &player_cnt))
			return (free(first_line), 0);
		free(first_line);
	}
	return (check_player_count(player_cnt));
}

int	find_max_width(char **map)
{
	int	max_width;
	int	i;
	int	len;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

int	process_and_validate_map(t_game *game)
{
	char	**padded_map;
	char	**processed_map;
	int		player_pos[2];

	printf("\n======= PROCESSING MAP =======");
	print_map_debug(game->map.raw_map, "Raw Map");
	game->map.width = find_max_width(game->map.raw_map);
	printf("  ✓ Width: %d x Height: %d\n\n", game->map.width, game->map.height);
	padded_map = pad_map_to_rectangle(game->map.raw_map);
	if (!padded_map)
		return (write(2, "Error: Failed to pad map\n", 25), 0);
	print_map_debug(padded_map, "Padded Map");
	processed_map = convert_interior_spaces_to_floor(padded_map);
	if (!processed_map)
		return (cleanup_padded(padded_map), 0);
	print_map_debug(processed_map, "Processed Map (spaces INTO 0's)");
	if (!validate_map_enclosure(processed_map))
		return (cleanup_both(padded_map, processed_map), 0);
	player_pos[0] = game->player.raw_y;
	player_pos[1] = game->player.raw_x;
	if (!validate_player_and_entities_reachable(processed_map, player_pos))
		return (cleanup_both(padded_map, processed_map), 0);
	finalize_map_processing(game, padded_map, processed_map);
	return (1);
}
