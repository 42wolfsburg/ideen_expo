/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:12:57 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:17:56 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	set_color(int rgb[3], int target[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		target[i] = rgb[i];
		i++;
	}
}

int	ft_parse_rgb(char **rgb_str, int rgb[3])
{
	int	i;
	int	len;

	i = 0;
	while (i < 3)
	{
		if (!rgb_str[i] || !ft_isdigit_str(rgb_str[i]))
			return (0);
		len = ft_strlen(rgb_str[i]);
		if (len > 1 && rgb_str[i][0] == '0')
		{
			printf("Error:  Leading zeros in RGB value: %s\n", rgb_str[i]);
			return (0);
		}
		rgb[i] = ft_atoi(rgb_str[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	if (rgb_str[3])
		return (0);
	return (1);
}

int	apply_valid_color(t_game *game, char **rgb_str, int rgb[3], int is_floor)
{
	if (is_floor)
	{
		if (game->floor_color[0] != -1)
		{
			free_strings(rgb_str);
			write(2, "Error: Duplicate floor color\n", 29);
			return (0);
		}
		set_color(rgb, game->floor_color);
	}
	else
	{
		if (game->ceiling_color[0] != -1)
		{
			free_strings(rgb_str);
			write(2, "Error: Duplicate ceiling color\n", 31);
			return (0);
		}
		set_color(rgb, game->ceiling_color);
	}
	free_strings(rgb_str);
	return (1);
}
