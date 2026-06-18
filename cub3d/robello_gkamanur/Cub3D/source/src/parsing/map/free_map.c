/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:53:57 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 20:03:43 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

static void	free_char_matrix(char **matrix, int height)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static void	reset_map_info(t_map *map)
{
	map->width = 0;
	map->height = 0;
}

void	free_map(t_data *data)
{
	free_char_matrix(data->map.grid, data->map.height);
	data->map.grid = NULL;
	if (data->map.first_line)
	{
		free(data->map.first_line);
		data->map.first_line = NULL;
	}
	reset_map_info(&data->map);
}

// void	free_map(t_data *data)
// {
// 	int	i;

// 	if (data->map.grid)
// 	{
// 		i = 0;
// 		while (i < data->map.height)
// 		{
// 			free(data->map.grid[i]);
// 			i++;
// 		}
// 		free(data->map.grid);
// 		data->map.grid = NULL;
// 	}
// 	if (data->map.door_states)
// 	{
// 		i = 0;
// 		while (i < data->map.height)
// 		{
// 			free(data->map.door_states[i]);
// 			i++;
// 		}
// 		free(data->map.door_states);
// 		data->map.door_states = NULL;
// 	}
// 	if (data->map.first_line)
// 	{
// 		free(data->map.first_line);
// 		data->map.first_line = NULL;
// 	}
// 	data->map.width = 0;
// 	data->map.height = 0;
// 	data->map.door_count = 0;
// }