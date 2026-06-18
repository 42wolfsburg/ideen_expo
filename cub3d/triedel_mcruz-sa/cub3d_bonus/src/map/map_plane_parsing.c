/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_plane_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:26 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/07 13:02:28 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	map_find_available_object_slot(t_map *map)
{
	int	j;

	j = 0;
	while (j < map->objcount)
	{
		if ((*map).obj[j].pos.x == -1 || (*map).obj[j].width == -1
			|| (*map).obj[j].normal.x == -1)
			break ;
		j++;
	}
	return (j);
}

void	map_parse_plane_details(t_map *map, int j, char **coordinates)
{
	int	i;

	i = 0;
	while (coordinates[i] != NULL)
	{
		if (ft_strncmp(coordinates[i], "PLN", 3) == 0)
		{
			i++;
			map_parse_plane_coordinates(map, j, coordinates, &i);
		}
		else if (map->obj[j].width == -1 && map->obj[j].height == -1)
			map_parse_plane_w_and_h(map, j, coordinates, &i);
		else if (map->obj[j].normal.x == -1 && map->obj[j].normal.y == -1)
			map_parse_normal_vector(map, j, coordinates, &i);
		else
			(*map).obj[j].texture_id = map_safe_ft_atoi(coordinates[i]);
		i++;
	}
}

void	map_parse_normal_vector(t_map *map, int j, char **coordinates, int *i)
{
	char	**string;

	string = ft_split(coordinates[*i], ',');
	(*map).obj[j].normal.x = map_ft_atof(string[0]);
	(*map).obj[j].normal.y = map_ft_atof(string[1]);
	(*map).obj[j].normal = vec_normalize((*map).obj[j].normal);
	map_free_double_array(string);
	string = NULL;
}

void	map_parse_plane_w_and_h(t_map *map, int j, char **coordinates, int *i)
{
	char	**string;

	string = ft_split(coordinates[*i], ',');
	(*map).obj[j].width = map_ft_atof(string[0]);
	(*map).obj[j].height = map_ft_atof(string[1]);
	map_free_double_array(string);
	string = NULL;
}

void	map_parse_plane_coordinates(t_map *map, int j, char **coordinates,
		int *i)
{
	char	**string;

	string = ft_split(coordinates[*i], ',');
	(*map).obj[j].pos.x = map_ft_atof(string[0]);
	(*map).obj[j].pos.y = map_ft_atof(string[1]);
	(*map).obj[j].pos.z = map_ft_atof(string[2]);
	map_free_double_array(string);
	string = NULL;
}
