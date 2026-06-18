/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:28 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 10:39:59 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*create_node(char *line)
{
	t_map	*new_node;

	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->line = line;
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_map **head, t_map *new_node)
{
	t_map	*temp;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	find_player_pos(t_game *game)
{
	t_map	*temp;
	int		row;
	int		col;

	temp = game->map;
	row = 0;
	while (temp != NULL)
	{
		col = 0;
		while (temp->line[col])
		{
			if (temp->line[col] == 'P')
			{
				game->player_y = row;
				game->player_x = col;
				return ;
			}
			col++;
		}
		temp = temp->next;
		row++;
	}
}

int	check_unreachable(t_map *head)
{
	t_map	*temp;
	int		i;

	temp = head;
	while (temp != NULL)
	{
		i = 0;
		while (temp->line[i] != '\0')
		{
			if (temp->line[i] == 'C' || temp->line[i] == 'E')
				return (0);
			i++;
		}
		temp = temp->next;
	}
	return (1);
}
