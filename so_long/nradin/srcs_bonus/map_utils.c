/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:22:39 by nradin            #+#    #+#             */
/*   Updated: 2023/03/03 14:35:49 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	components_ifs(char c, t_comp *comps)
{
	if (c == MAP_EXIT)
		comps->exit += 1;
	else if (c == PLAYER)
		comps->player += 1;
	else if (c == COLLECTIBLE)
		comps->collect += 1;
	else if (c == ENEMY_HORIZONTAL || c == ENEMY_VERTICAL)
		comps->enemy += 1;
	else if (c != WALL && c != FLOOR && c != '\n')
		return (0);
	return (1);
}

void	count_components(t_game *game, char **map, t_comp *comps)
{
	int	i;
	int	j;

	i = 0;
	init_comp(comps);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!components_ifs(map[i][j], comps))
				throw_error(game, comps, MAP_INVALID_CHARACTERS_ERROR);
			j++;
		}
		i++;
	}
}
