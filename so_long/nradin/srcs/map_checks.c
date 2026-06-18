/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:03 by nradin            #+#    #+#             */
/*   Updated: 2023/03/03 13:13:27 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_rectangular(char **map)
{
	int	i;

	if (!map || !map[0])
		return (0);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i - 1]) != ft_strlen(map[i]))
			return (0);
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	if (!map || !map[0])
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == (int)ft_strstr_len(map) - 1 || \
				j == 0 || j == (int)ft_strlen(map[i]) - 2) && \
				map[i][j] != WALL && map[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_comp	*check_components(t_game *game, char **map)
{
	t_comp	*comps;

	if (!map || !map[0])
		return (NULL);
	comps = ft_calloc(sizeof(t_comp), 1);
	count_components(game, map, comps);
	if (comps->exit != 1 || comps->player != 1 || comps->collect < 1)
		throw_error(game, comps, MAP_COMPONENTS_ERROR);
	return (comps);
}

void	check_map(t_game *game)
{
	t_comp	*comps;

	comps = check_components(game, game->map);
	if (!check_rectangular(game->map))
		throw_error(game, comps, MAP_RECT_ERROR);
	if (!check_walls(game->map))
		throw_error(game, comps, MAP_WALL_ERROR);
	if (!find_path(game, comps))
		throw_error(game, comps, MAP_PATH_ERROR);
	free(comps);
}
