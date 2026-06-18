/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:41 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/13 14:47:38 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	map_init_values(t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->grid = NULL;
	map->spawn_x = 0;
	map->spawn_y = 0;
	map->map_textures = NULL;
	map->direction = '\0';
	map->floor = CTRANSPARENT;
	map->ceiling = CTRANSPARENT;
	map->ceil_color.red = -1;
	map->ceil_color.green = -1;
	map->ceil_color.blue = -1;
	map->floor_color.red = -1;
	map->ceil_color.green = -1;
	map->ceil_color.blue = -1;
	map->txtcount = 0;
	map->objcount = 0;
	map->introcount = 0;
	map->intro_phrases = NULL;
	map->txt_index = 4;
	map->intro_index = 0;
	map->obj = NULL;
}

void	map_print(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		printf("%s\n", map->grid[y]);
		y++;
	}
}

void	map_direction_validation(char *line, int flag)
{
	if (flag != 1)
	{
		free(line);
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
}

int	map_open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		errexit(ERROR_9);
	return (fd);
}
