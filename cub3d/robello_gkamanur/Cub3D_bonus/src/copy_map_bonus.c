/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:32:07 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 23:07:57 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_map_character(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'C' || c == 'X' || c == 'D' || c == 'T');
}

int	is_map_char(char c)
{
	if (c == '\t')
	{
		printf("Error:  Tab character detected (ASCII %d)\n", c);
		return (0);
	}
	if (c == '\r')
		return (0);
	return (c == FLOOR || c == WALL || ft_strchr("NSEW", c) || c == DOOR
		|| c == SECRET || c == COLL || c == ENEMY || c == ' ');
}

char	**copy_map_for_flood_fill(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i = i + 1;
	}
	copy[height] = NULL;
	return (copy);
}

char	**ft_copy_map(char **map, int height)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (height + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < height)
	{
		temp[i] = ft_strdup(map[i]);
		if (!temp[i])
		{
			while (--i >= 0)
				free(temp[i]);
			free(temp);
			return (NULL);
		}
		i++;
	}
	temp[height] = NULL;
	return (temp);
}

int	check_map_cells(char **map, int h, int w)
{
	int	i;
	int	j;
	int	pos[2];
	int	dims[2];

	dims[0] = h;
	dims[1] = w;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (is_map_character(map[i][j]))
			{
				pos[0] = i;
				pos[1] = j;
				if (check_cell_enclosure(map, pos, dims) == 0)
					return (0);
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return (1);
}
