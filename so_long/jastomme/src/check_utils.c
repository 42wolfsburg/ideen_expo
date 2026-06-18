/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:00:04 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 10:44:51 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
if wall is != '1'
*/
int	is_wall_line(const char *line, size_t width)
{
	size_t	i;

	i = 0;
	while (i < width)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

char	get_char_at(t_map *head, size_t row, size_t col)
{
	t_map	*temp;
	size_t	current_row;

	temp = head;
	current_row = 0;
	while (temp != NULL && current_row < row)
	{
		temp = temp->next;
		current_row++;
	}
	if (temp == NULL || col >= ft_strlen(temp->line))
		return ('\0');
	return (temp->line[col]);
}

void	set_char_at(t_map *head, size_t row, size_t col, char new_char)
{
	t_map	*temp;
	size_t	current_row;

	temp = head;
	current_row = 0;
	while (temp != NULL && current_row < row)
	{
		temp = temp->next;
		current_row++;
	}
	if (temp == NULL || col >= ft_strlen(temp->line))
		return ;
	temp->line[col] = new_char;
}

void	flood_fill(t_map *head, size_t x, size_t y)
{
	size_t		width;
	size_t		height;
	char		current_char;

	width = 0;
	height = 0;
	get_map_dimensions(head, &width, &height);
	if (x < 0 || x >= height || y < 0 || y >= width)
		return ;
	current_char = get_char_at(head, x, y);
	if (current_char == '1' || current_char == 'F' || current_char == 'Z')
		return ;
	if (current_char == 'C' || current_char == 'E' || current_char == '0'
		|| current_char == 'P')
		set_char_at(head, x, y, 'F');
	flood_fill(head, x + 1, y);
	flood_fill(head, x - 1, y);
	flood_fill(head, x, y + 1);
	flood_fill(head, x, y - 1);
}

void	get_map_dimensions(t_map *head, size_t *width, size_t *height)
{
	t_map	*temp;

	temp = head;
	*height = 1;
	*width = 0;
	while (temp->next != NULL)
	{
		if (ft_strlen(temp->line) > *width)
			*width = ft_strlen(temp->line);
		(*height)++;
		temp = temp->next;
	}
}
