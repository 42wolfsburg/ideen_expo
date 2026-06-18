/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:55:26 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 20:05:00 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parsing.h"

char	**allocate_temp_lines(int size)
{
	char	**temp;

	temp = malloc(sizeof(char *) * size);
	return (temp);
}

void	free_temp_lines(char **lines, int count)
{
	while (count-- > 0)
		free(lines[count]);
	free(lines);
}

// static int	allocate_map_arrays(t_data *data, int count)
// {
// 	data->map.grid = malloc(sizeof(char *) * (count + 1));
// 	if (!data->map.grid)
// 		return (0);
// 	data->map.door_states = malloc(sizeof(char *) * (count + 1));
// 	if (!data->map.door_states)
// 	{
// 		free(data->map.grid);
// 		return (0);
// 	}
// 	return (1);
// }

// static int	init_door_states(t_data *data, int count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		data->map.door_states[i] = malloc(data->map.width + 1);
// 		if (!data->map.door_states[i])
// 		{
// 			while (--i >= 0)
// 				free(data->map.door_states[i]);
// 			free(data->map.door_states);
// 			free(data->map.grid);
// 			return (0);
// 		}
// 		ft_memset(data->map.door_states[i], '0', data->map.width);
// 		data->map.door_states[i][data->map.width] = '\0';
// 		i++;
// 	}
// 	data->map.door_states[count] = NULL;
// 	return (1);
// }

// int	allocate_grid(t_data *data, char **temp_lines, int count)
// {
// 	data->map.height = count;
// 	data->map.width = get_max_width(temp_lines, count);
// 	if (!allocate_map_arrays(data, count))
// 		return (0);
// 	if (!init_door_states(data, count))
// 		return (0);
// 	return (1);
// }

// int	allocate_grid(t_data *data, char **temp_lines, int count)
// {
// 	int	i;

// 	data->map.height = count;
// 	data->map.width = get_max_width(temp_lines, count);
// 	data->map.grid = malloc(sizeof(char *) * (count + 1));
// 	if (!data->map.grid)
// 		return (0);
// 	data->map.door_states = malloc(sizeof(char *) * (count + 1));
// 	if (!data->map.door_states)
// 	{
// 		free(data->map.grid);
// 		return (0);
// 	}
// 	i = 0;
// 	while (i < count)
// 	{
// 		data->map.door_states[i] = malloc(data->map.width + 1);
// 		if (!data->map.door_states[i])
// 		{
// 			while (--i >= 0)
// 				free(data->map.door_states[i]);
// 			free(data->map.door_states);
// 			free(data->map.grid);
// 			return (0);
// 		}
// 		ft_memset(data->map.door_states[i], '0', data->map.width);
// 		data->map.door_states[i][data->map.width] = '\0';
// 		i++;
// 	}
// 	data->map.door_states[count] = NULL;
// 	return (1);
// }