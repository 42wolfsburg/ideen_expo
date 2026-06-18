/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:44:01 by robello           #+#    #+#             */
/*   Updated: 2026/01/25 18:18:19 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*pad_line_to_width(char *line, int target_width)
{
	char	*padded;
	int		i;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len && line[i] && line[i] != '\n')
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
		padded[i++] = ' ';
	padded[target_width] = '\0';
	return (padded);
}

char	**pad_map_lines(char **map, int height, int max_width)
{
	char	**padded;
	int		i;

	padded = malloc(sizeof(char *) * (height + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < height)
	{
		padded[i] = pad_line_to_width(map[i], max_width);
		if (!padded[i])
		{
			while (--i >= 0)
				free(padded[i]);
			free(padded);
			return (NULL);
		}
		i++;
	}
	padded[height] = NULL;
	return (padded);
}

char	**pad_map_to_rectangle(char **map)
{
	int	height;
	int	max_width;

	if (!map)
		return (NULL);
	height = 0;
	while (map[height])
		height++;
	max_width = find_max_width(map);
	return (pad_map_lines(map, height, max_width));
}

int	check_cell_enclosure(char **map, int pos[2], int dims[2])
{
	int	i;
	int	j;

	i = pos[0];
	j = pos[1];
	if (i == 0 || i == dims[0] - 1 || j == 0 || j == dims[1] - 1)
	{
		printf("\nError: Map not enclosed at edge map@ [%d,%d]\n",
			i + 1, j + 1);
		printf("       Character '%c' is on the map boundary\n", map[i][j]);
		return (0);
	}
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
		|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
	{
		printf("\nError: Map not enclosed, adjacent to void, map@ [%d,%d]\n",
			i + 1, j + 1);
		printf("       Character '%c' has empty space next to it\n\n",
			map[i][j]);
		return (0);
	}
	return (1);
}

int	validate_map_enclosure(char **map)
{
	int	h;
	int	w;

	if (!map || !map[0])
		return (0);
	h = 0;
	while (map[h])
		h = h + 1;
	w = ft_strlen(map[0]);
	return (check_map_cells(map, h, w));
}
