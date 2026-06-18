/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_coordinates_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:01:56 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/13 14:47:37 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	map_texture(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "TXT ", 4) == 0 && map_last_new_line(line))
	{
		new_string = ft_strdup(line + ft_strlen("TXT "));
		if (map->txt_index < map->txtcount + 1)
		{
			map->map_textures[map->txt_index++] = ft_strdup(new_string);
			free(new_string);
			return (1);
		}
	}
	return (0);
}

int	map_intro(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "INTRO ", 6) == 0)
	{
		new_string = ft_strdup(line + ft_strlen("INTRO "));
		if (map_last_new_line(new_string))
			map->intro_phrases[map->intro_index++] = ft_strdup(new_string);
		free(new_string);
		return (1);
	}
	return (0);
}

int	map_next_lvl(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "LVL ", 3) == 0 && map_last_new_line(line))
	{
		map->level = ft_strdup(line + ft_strlen("LVL "));
		return (1);
	}
	return (0);
}

void	map_find_direction(t_map *map, char *line, int *flag, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
			|| line[x] == 'W')
		{
			(*flag)++;
			map->direction = line[x];
			map->spawn_x = x;
			map->spawn_y = y;
		}
		x++;
	}
}

void	map_process_row(t_map *map, char *line, int *y)
{
	int	i;

	map->grid[*y] = (char *)ft_calloc(map->width + 1, sizeof(char));
	if (!map->grid[*y])
		errexit(ERROR_8);
	map_last_new_line(line);
	i = 0;
	while (line[i] != '\0' && i < map->width)
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			map->grid[*y][i] = '0';
		else
			map->grid[*y][i] = line[i];
		i++;
	}
	(*y)++;
}
