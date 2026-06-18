/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:55:55 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:08:45 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*remove_carriage_returns(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\r')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	validate_header_format(char *trimmed)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0 || ft_strncmp(trimmed, "WE ", 3)
		== 0 || ft_strncmp(trimmed, "EA ", 3) == 0)
		return (ft_validate_texture_header(trimmed));
	else if (ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0)
		return (ft_validate_color_header(trimmed));
	return (1);
}

int	check_if_map_line(char *trimmed)
{
	int	i;

	i = 0;
	while (trimmed[i] && trimmed[i] != '\n')
	{
		if (!is_map_char(trimmed[i]))
		{
			printf("Error:  Line is not a valid header/map character: '%s'\n",
				trimmed);
			printf("        Character '%c' at position %d is not allowed\n",
				trimmed[i], i);
			return (0);
		}
		i = i + 1;
	}
	return (-1);
}

int	parse_color(t_game *game, char *line, int is_floor)
{
	char	**rgb_str;
	int		rgb[3];
	char	*trimmed;

	trimmed = ft_strtrim(line + 2, " \t\r\n");
	if (!trimmed)
		return (0);
	rgb_str = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb_str || !ft_parse_rgb(rgb_str, rgb))
	{
		free_strings(rgb_str);
		write(2, "Error:  Invalid RGB color\n", 26);
		return (0);
	}
	return (apply_valid_color(game, rgb_str, rgb, is_floor));
}

int	process_header_line(t_game *game, char *trimmed, int *headers_found)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (parse_and_count(game, trimmed, WALL_N, headers_found));
	if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (parse_and_count(game, trimmed, WALL_S, headers_found));
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (parse_and_count(game, trimmed, WALL_W, headers_found));
	if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (parse_and_count(game, trimmed, WALL_E, headers_found));
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		if (!parse_color(game, trimmed, 1))
			return (0);
		*headers_found = *headers_found + 1;
		return (1);
	}
	if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (!parse_color(game, trimmed, 0))
			return (0);
		*headers_found = *headers_found + 1;
		return (1);
	}
	return (check_if_map_line(trimmed));
}
