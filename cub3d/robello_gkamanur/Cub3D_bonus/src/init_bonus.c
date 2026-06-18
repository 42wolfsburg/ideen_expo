/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:48:40 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 17:49:13 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	parse_all_headers(int fd, t_game *game, char **first_line, int *line_num)
{
	char	*line;
	int		headers_found;

	headers_found = 0;
	*line_num = 0;
	line = get_next_line(fd);
	while (line)
	{
		*line_num = *line_num + 1;
		if (!process_header_line_wrapper(game, line, line_num, &headers_found))
			return (free(line), 0);
		if (headers_found == 6)
		{
			*first_line = find_first_map_line(fd, line_num);
			if (*first_line)
				printf("  ✓ Map starts at FILE line %d\n", *line_num);
			return (1);
		}
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_cub_file(int fd, t_game *game)
{
	char	*first_map_line;
	int		current_file_line;

	printf("\n======= PARSING HEADERS =======\n\n");
	if (!parse_all_headers(fd, game, &first_map_line, &current_file_line))
		return (0);
	if (!validate_all_headers(game))
	{
		if (first_map_line)
			free(first_map_line);
		return (0);
	}
	debug_texture_loading(game);
	if (!parse_and_validate_map(fd, game, first_map_line, current_file_line))
		return (0);
	return (setup_bonus_entities(game));
}

int	validate_input(char **av)
{
	size_t	len;
	size_t	i;
	char	*name;
	int		fd;

	name = av[1];
	len = ft_strlen(name);
	if (len < 5)
		return (write(2, "Error: File must be .cub extension\n", 36), -1);
	if (ft_strncmp(name + len - 4, ".cub", 4) != 0)
		return (write(2, "Error: File must be .cub extension\n", 36), -1);
	i = 0;
	while (i < len - 4)
	{
		if (name[i] == '.' && ft_strncmp(name + i, ".cub", 4) == 0)
			return (write(2, "Error: Multiple .cub in filename\n", 34), -1);
		i++;
	}
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Opening file failed");
		return (-1);
	}
	return (fd);
}

void	ft_init_colors(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		game->floor_color[i] = -1;
		game->ceiling_color[i] = -1;
		i++;
	}
}

void	ft_init_systems_struct(t_game *game)
{
	game->doors.list = NULL;
	game->doors.count = 0;
	game->doors.secret_cnt = 0;
	game->doors.door_speed = DOOR_SPEED;
	game->enemies.list = NULL;
	game->enemies.ene_count = 0;
	game->colls.list = NULL;
	game->colls.total = 0;
	game->colls.collected = 0;
	game->sprites.list = NULL;
	game->sprites.count = 0;
	game->sprites.zbuffer = NULL;
	game->sprites.zbuffer_w = 0;
	game->map.raw_map = NULL;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player.raw_x = -1;
	game->player.raw_y = -1;
	game->player.start_char = '\0';
}
