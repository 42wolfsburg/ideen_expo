/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:01:23 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/13 14:47:36 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	map_grid_allocation(t_map *map, char *path)
{
	int		y;
	int		fd;
	char	*line;

	map_obj_allocation(map);
	fd = map_open_file(path);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL && line)
	{
		if (map_color_texture_check(line))
			map_store_textures_and_colors(map, line);
		else
			map_process_row(map, line, &y);
		free(line);
		line = get_next_line(fd);
	}
	map->grid[y] = NULL;
	close(fd);
}

void	map_obj_allocation(t_map *map)
{
	int	i;

	map->grid = map_calloc(map);
	map->obj = ft_calloc(map->objcount + 1, sizeof(t_obj));
	map->intro_phrases = ft_calloc(map->introcount + 1, sizeof(char *));
	if (!map->intro_phrases)
	{
		free(map->obj);
		exit(EXIT_FAILURE);
	}
	map->map_textures = ft_calloc(map->txtcount + 1, sizeof(char *));
	if (!map->map_textures)
	{
		free(map->obj);
		exit(EXIT_FAILURE);
	}
	map->map_textures[map->txtcount] = NULL;
	i = 0;
	while (i < map->objcount + 1)
	{
		map_init_map_obj(map, i);
		i++;
	}
}

void	map_init_map_obj(t_map *map, int index)
{
	map->obj[index].width = -1;
	map->obj[index].height = -1;
	map->obj[index].pos.x = -1;
	map->obj[index].pos.y = -1;
	map->obj[index].pos.z = -1;
	map->obj[index].pos.z = -1;
	map->obj[index].normal.x = -1;
	map->obj[index].normal.y = -1;
}

char	**map_calloc(t_map *map)
{
	map->grid = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		errexit(ERROR_8);
	return (map->grid);
}

char	**map_copy_allocation(t_map *map)
{
	int		i;
	char	**copy;

	i = 0;
	copy = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!copy)
		errexit(ERROR_8);
	while (i < map->height)
	{
		copy[i] = (char *)ft_strdup(map->grid[i]);
		if (!copy[i])
			errexit(ERROR_8);
		i++;
	}
	return (copy);
}
