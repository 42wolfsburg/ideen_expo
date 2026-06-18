/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_it.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:59:56 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 11:52:04 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
checks if the map is rectangular:
go through every line of the map and check if length is equal
*/
int	is_rectangular(t_game *game)
{
	size_t	width;
	t_map	*temp;
	size_t	count;

	count = 0;
	if (game->map == NULL || game->map->line == NULL)
		return (0);
	width = ft_strlen(game->map->line);
	temp = game->map->next;
	while (temp != NULL)
	{
		if (ft_strlen(temp->line) != width)
			return (0);
		count++;
		temp = temp->next;
	}
	if (count > 16 || width > 32)
		return (0);
	return (1);
}

/*
check if walls are closed:
check first line, iterate through list to last line
check in betweens for '1' on first and last char
*/
int	closed_walls(t_game *game)
{
	t_map	*temp;
	size_t	width;

	if (game->map == NULL || game->map->line == NULL)
		return (0);
	width = ft_strlen(game->map->line);
	temp = game->map;
	if (!is_wall_line(temp->line, width))
		return (0);
	while (temp->next != NULL)
		temp = temp->next;
	if (!is_wall_line(temp->line, width))
		return (0);
	temp = game->map->next;
	while (temp->next != NULL)
	{
		if (temp->line[0] != '1' || temp->line[width - 1] != '1')
			return (0);
		temp = temp->next;
	}
	return (1);
}

/*
checks line by line and returns if P,C,E == 1;
*/
int	check_elements(t_game *game)
{
	t_map	*temp;
	size_t	i;

	game->p_count = 0;
	game->e_count = 0;
	game->c_count = 0;
	temp = game->map;
	while (temp != NULL)
	{
		i = 0;
		while (temp->line[i] != '\0')
		{
			if (temp->line[i] == 'P')
				game->p_count++;
			else if (temp->line[i] == 'C')
				game->c_count++;
			else if (temp->line[i] == 'E')
				game->e_count++;
			i++;
		}
		temp = temp->next;
	}
	return (game->p_count == 1 && game->c_count >= 1 && game->e_count == 1);
}

/*
checks if any other character than 1,0,C,P,E
*/
int	only_valid_elements(t_game *game)
{
	t_map	*temp;
	size_t	i;

	temp = game->map;
	while (temp != NULL)
	{
		i = 0;
		while (temp->line[i] != '\0')
		{
			if (temp->line[i] != '1' && temp->line[i] != '0'
				&& temp->line[i] != 'C' && temp->line[i] != 'P'
				&& temp->line[i] != 'E')
				return (0);
			i++;
		}
		temp = temp->next;
	}
	return (1);
}

int	path_is_valid(t_game *game)
{
	find_player_pos(game);
	flood_fill(game->map, game->player_y, game->player_x);
	return (check_unreachable(game->map));
}
