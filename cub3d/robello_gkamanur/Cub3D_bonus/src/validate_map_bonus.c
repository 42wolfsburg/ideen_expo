/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:20:33 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:22:57 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	process_first_line(t_game *game, char *line, int file_line, int *player_cnt)
{
	int	data[2];

	data[0] = *player_cnt;
	data[1] = 1;
	if (!process_any_line(game, line, file_line, data))
		return (0);
	*player_cnt = data[0];
	return (1);
}

char	**add_line(char **map, char *line, int size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = map[i];
		i++;
	}
	new[i++] = ft_strdup(line);
	new[i] = NULL;
	if (map)
		free(map);
	return (new);
}

int	process_any_line(t_game *game, char *line, int file_line, int data[2])
{
	char	*clean;
	int		line_data[3];

	clean = remove_carriage_returns(line);
	if (!clean)
		return (cleanup_on_error(NULL, line, data[1]));
	if (clean[0] == '\0' || is_empty(clean))
	{
		print_empty_line_error(file_line, data[1]);
		return (cleanup_on_error(clean, line, data[1]));
	}
	line_data[0] = file_line;
	line_data[1] = game->map.height;
	line_data[2] = data[1];
	if (!validate_all_chars(game, clean, line_data, &data[0]))
		return (cleanup_on_error(clean, line, data[1]));
	game->map.raw_map = add_line(game->map.raw_map, clean, game->map.height++);
	free(clean);
	if (data[1])
		free(line);
	return (1);
}

int	process_next_line(t_game *game, char *line, int file_line, int *player_cnt)
{
	int	data[2];

	data[0] = *player_cnt;
	data[1] = 0;
	if (!process_any_line(game, line, file_line, data))
		return (0);
	*player_cnt = data[0];
	return (1);
}

int	validate_all_headers(t_game *game)
{
	if (!game->tex.tex[WALL_N].img)
		return (write(2, "Error: Missing NO texture\n", 26), 0);
	if (!game->tex.tex[WALL_S].img)
		return (write(2, "Error: Missing SO texture\n", 26), 0);
	if (!game->tex.tex[WALL_E].img)
		return (write(2, "Error: Missing EA texture\n", 26), 0);
	if (!game->tex.tex[WALL_W].img)
		return (write(2, "Error: Missing WE texture\n", 26), 0);
	if (game->floor_color[0] == -1)
		return (write(2, "Error: Missing floor color\n", 27), 0);
	if (game->ceiling_color[0] == -1)
		return (write(2, "Error: Missing ceiling color\n", 29), 0);
	return (1);
}
