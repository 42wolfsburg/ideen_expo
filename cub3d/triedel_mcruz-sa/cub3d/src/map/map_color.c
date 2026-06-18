/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:01:49 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/07 13:01:51 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	map_floor_color(t_map *map, char *line)
{
	char	*new_string;
	char	**colors;

	new_string = NULL;
	colors = NULL;
	if (ft_strncmp(line, "F", 1) == 0)
	{
		new_string = ft_strtrim(line, "F ");
		colors = ft_split(new_string, ',');
		free(new_string);
		(*map).floor_color.red = map_safe_ft_atoi(colors[0]);
		(*map).floor_color.green = map_safe_ft_atoi(colors[1]);
		(*map).floor_color.blue = map_safe_ft_atoi(colors[2]);
		if ((*map).floor_color.red == -1 || (*map).floor_color.green == -1
			|| (*map).floor_color.blue == -1)
		{
			map_free_double_array(colors);
			exit(EXIT_FAILURE);
		}
		map->floor = map_combine_rgb(map->floor_color.red,
				map->floor_color.green, map->floor_color.blue);
		map_free_double_array(colors);
		return (1);
	}
	return (0);
}

int	map_ceiling_color(t_map *map, char *line)
{
	char	*new_string;
	char	**colors;

	new_string = NULL;
	colors = NULL;
	if (ft_strncmp(line, "C", 1) == 0)
	{
		new_string = ft_strtrim(line, "C ");
		colors = ft_split(new_string, ',');
		free(new_string);
		(*map).ceil_color.red = map_safe_ft_atoi(colors[0]);
		(*map).ceil_color.green = map_safe_ft_atoi(colors[1]);
		(*map).ceil_color.blue = map_safe_ft_atoi(colors[2]);
		if ((*map).ceil_color.red == -1 || (*map).ceil_color.green == -1
			|| (*map).ceil_color.blue == -1)
		{
			map_free_double_array(colors);
			exit(EXIT_FAILURE);
		}
		map->ceiling = map_combine_rgb(map->ceil_color.red,
				map->ceil_color.green, map->ceil_color.blue);
		map_free_double_array(colors);
		return (1);
	}
	return (0);
}

void	map_store_textures_and_colors(t_map *map, char *line)
{
	if (map_no_coordinate(map, line))
		return ;
	else if (map_so_coordinate(map, line))
		return ;
	else if (map_we_coordinate(map, line))
		return ;
	else if (map_ea_coordinate(map, line))
		return ;
	else if (map_texture(map, line))
		return ;
	else if (map_intro(map, line))
		return ;
	else if (map_next_lvl(map, line))
		return ;
	else if (map_floor_color(map, line) && map_last_new_line(line))
		return ;
	else if (map_ceiling_color(map, line) && map_last_new_line(line))
		return ;
	else if (map_plane_texture(map, line) && map_last_new_line(line))
		return ;
}

int	map_plane_texture(t_map *map, char *line)
{
	char	**coordinates;
	int		j;

	coordinates = NULL;
	j = map_find_available_object_slot(map);
	if (j == map->objcount)
	{
		return (0);
	}
	if (ft_strncmp(line, "PLN", 3) == 0)
	{
		coordinates = ft_split(line, ' ');
		(*map).obj[j].type = OBJ_PLANE;
		map_parse_plane_details(map, j, coordinates);
	}
	map_free_double_array(coordinates);
	return (0);
}

unsigned int	map_combine_rgb(unsigned int red,
		unsigned int green,
		unsigned int blue)
{
	return ((red << 16 | (green << 8) | blue));
}
