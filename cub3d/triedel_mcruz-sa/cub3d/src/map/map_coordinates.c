/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:03 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/07 13:02:06 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	map_xy_coordinates(t_map *map, char *path)
{
	int		y;
	int		fd;
	int		flag;
	char	*line;

	fd = map_open_file(path);
	flag = 0;
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!map_color_texture_check(line))
		{
			map_find_direction(map, line, &flag, y);
			y++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map_direction_validation(line, flag);
}

int	map_no_coordinate(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0 && map_last_new_line(line))
	{
		new_string = ft_strdup(line + ft_strlen("NO "));
		map->map_textures[DNORTH] = ft_strdup(new_string);
		free(new_string);
		return (1);
	}
	return (0);
}

int	map_so_coordinate(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "SO ", 3) == 0 && map_last_new_line(line))
	{
		new_string = ft_strdup(line + ft_strlen("SO "));
		map->map_textures[DSOUTH] = ft_strdup(new_string);
		free(new_string);
		return (1);
	}
	return (0);
}

int	map_we_coordinate(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "WE ", 3) == 0 && map_last_new_line(line))
	{
		new_string = ft_strdup(line + ft_strlen("WE "));
		map->map_textures[DWEST] = ft_strdup(new_string);
		free(new_string);
		return (1);
	}
	return (0);
}

int	map_ea_coordinate(t_map *map, char *line)
{
	char	*new_string;

	new_string = NULL;
	if (ft_strncmp(line, "EA ", 3) == 0 && map_last_new_line(line))
	{
		new_string = ft_strdup(line + ft_strlen("EA "));
		map->map_textures[DEAST] = ft_strdup(new_string);
		free(new_string);
	}
	return (0);
}
