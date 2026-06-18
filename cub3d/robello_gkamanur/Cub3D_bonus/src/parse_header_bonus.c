/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:59:51 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:09:43 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	ft_validate_texture_header(char *trimmed)
{
	int	i;

	i = 0;
	while (trimmed[i] && trimmed[i] != '\n')
	{
		if (trimmed[i] == '\t')
		{
			printf("Error: Tab character in texture header: %s\n", trimmed);
			return (0);
		}
		if (i >= 2 && trimmed[i] == ' ')
			break ;
		i = i + 1;
	}
	if (trimmed[2] != ' ')
	{
		printf("Error:  Missing space after texture identifier: %s\n", trimmed);
		return (0);
	}
	return (1);
}

int	ft_validate_color_header(char *trimmed)
{
	int	i;

	i = 0;
	while (trimmed[i] && trimmed[i] != '\n')
	{
		if (trimmed[i] == '\t')
		{
			printf("Error: Tab character in color header: %s\n", trimmed);
			return (0);
		}
		i = i + 1;
	}
	if (trimmed[1] != ' ')
	{
		printf("Error: Missing space after color identifier: %s\n", trimmed);
		return (0);
	}
	return (1);
}

int	parse_texture_path(t_game *game, char *line, t_text_id tex_id)
{
	char	*path;

	path = ft_strtrim(line + 3, " \t\r\n");
	if (!path || path[0] == '\0')
	{
		free(path);
		write(2, "Error: Missing texture path\n", 28);
		return (0);
	}
	if (game->tex.tex[tex_id].img)
	{
		free(path);
		write(2, "Error: Duplicate texture\n", 25);
		return (0);
	}
	game->tex.tex[tex_id] = load_tx(game->mlx, path);
	free(path);
	if (!game->tex.tex[tex_id].img)
		return (0);
	return (1);
}

int	parse_and_count(t_game *game, char *trimmed, int tex_id, int *count)
{
	if (!parse_texture_path(game, trimmed, tex_id))
		return (0);
	*count = *count + 1;
	return (1);
}
