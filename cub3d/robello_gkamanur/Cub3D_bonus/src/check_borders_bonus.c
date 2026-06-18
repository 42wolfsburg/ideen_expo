/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:24:36 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:43:07 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_mark_edges_horizontal(char **temp, int h, int w)
{
	int	i;
	int	p[2];

	i = 0;
	while (i < w)
	{
		p[0] = 0;
		p[1] = i;
		if (temp[0][i] == ' ')
			flood_fill(temp, p, 'V', ' ');
		p[0] = h - 1;
		if (temp[h - 1][i] == ' ')
			flood_fill(temp, p, 'V', ' ');
		i = i + 1;
	}
}

void	ft_mark_edges_vertical(char **temp, int h, int w)
{
	int	i;
	int	p[2];

	i = 0;
	while (i < h)
	{
		p[0] = i;
		p[1] = 0;
		if (temp[i][0] == ' ')
			flood_fill(temp, p, 'V', ' ');
		p[1] = w - 1;
		if (temp[i][w - 1] == ' ')
			flood_fill(temp, p, 'V', ' ');
		i = i + 1;
	}
}

char	**mark_edge_spaces_as_void(char **map)
{
	char	**temp;
	int		height;
	int		width;

	if (!map || !map[0])
		return (NULL);
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	temp = ft_copy_map(map, height);
	if (!temp)
		return (NULL);
	ft_mark_edges_horizontal(temp, height, width);
	ft_mark_edges_vertical(temp, height, width);
	return (temp);
}

void	convert_void_to_floor(char **result, char **void_map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (result[i][j])
		{
			if (void_map[i][j] == ' ')
				result[i][j] = '0';
			j++;
		}
		i++;
	}
}

char	**convert_interior_spaces_to_floor(char **map)
{
	char	**result;
	char	**void_map;
	int		height;

	if (!map)
		return (NULL);
	height = 0;
	while (map[height])
		height++;
	void_map = mark_edge_spaces_as_void(map);
	if (!void_map)
		return (NULL);
	result = ft_copy_map(map, height);
	if (!result)
	{
		free_strings(void_map);
		return (NULL);
	}
	convert_void_to_floor(result, void_map, height);
	free_strings(void_map);
	return (result);
}
