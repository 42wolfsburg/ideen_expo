/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:02:33 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/08/07 19:30:31 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	map_deinit(t_map *map)
{
	int	i;

	free(map->obj);
	map_deinit_doublepointer(map->intro_phrases);
	map_deinit_doublepointer(map->map_textures);
	i = 0;
	if (map->grid == NULL)
		return ;
	while (map->grid[i] != NULL)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map->level);
	map->grid = NULL;
}

void	map_deinit_doublepointer(char **dstr)
{
	int	i;

	i = -1;
	if (dstr == NULL)
		return ;
	while (dstr[++i] != NULL)
		free(dstr[i]);
	free(dstr);
	dstr = NULL;
}
