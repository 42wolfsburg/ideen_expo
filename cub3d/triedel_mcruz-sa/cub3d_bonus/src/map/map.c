/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:51 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/13 14:47:38 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// Initialize `map` by reading file from `path`
void	map_read(t_map *map, char *path)
{
	int		fd;
	int		in_header;
	char	*line;

	in_header = 1;
	fd = -1;
	if (!ft_endswith(path, MAP_SUFFIX))
		errexit(ERROR_3);
	fd = map_open_file(path);
	line = map_read_header(map, fd, &in_header);
	map_read_body(map, fd, line);
	close(fd);
	map_xy_coordinates(map, path);
	map_grid_allocation(map, path);
	map_validation(map);
}

char	*map_read_header(t_map *map, int fd, int *in_header)
{
	char	*line;

	line = get_next_line(fd);
	if (line && (line[0] == '1' || line[0] == '0'))
	{
		free(line);
		errexit(ERROR_4);
	}
	while (line != NULL && *in_header)
	{
		if (map_metadata_add(map, line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else
			*in_header = 0;
		if (*in_header)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	return (line);
}

void	map_read_body(t_map *map, int fd, char *line)
{
	int	len;
	int	end_of_map;

	end_of_map = 0;
	while (!end_of_map)
	{
		if (line == NULL)
		{
			end_of_map = 1;
			break ;
		}
		len = (int)ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			len--;
		if (len > 0)
			map->height++;
		else
			end_of_map = 1;
		if (len > map->width)
			map->width = len;
		free(line);
		line = get_next_line(fd);
		if (end_of_map && line != NULL)
			errexit(ERROR_5);
	}
}

int	map_last_new_line(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		return (1);
	}
	return (0);
}
