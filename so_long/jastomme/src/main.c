/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:00:13 by jastomme          #+#    #+#             */
/*   Updated: 2026/05/13 10:40:26 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

extern t_game	*g_game;

void	good_input(t_game *game)
{
	if (!is_rectangular(game))
		input_exit(game, "ERROR: Map not rectangular or too big\n");
	if (!closed_walls(game))
		input_exit(game, "ERROR: Map not closed by walls.\n");
	if (!only_valid_elements(game))
		input_exit(game, "ERROR: Invalid elements!\n");
	if (!check_elements(game))
		input_exit(game, "ERROR: Invalid number of elements.\n");
	if (!path_is_valid(game))
		input_exit(game, "ERROR: No valid path.\n");
}

static char	*trim_newline(char *line)
{
	size_t	len;

	if (line == NULL)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

t_map	*map_to_list(const char *file_path)
{
	int		fd;
	char	*line;
	t_map	*head;
	t_map	*new_node;

	head = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = trim_newline(line);
		new_node = create_node(line);
		if (!new_node)
			break ;
		append_node(&head, new_node);
		line = get_next_line(fd);
	}
	close(fd);
	return (head);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_printf("ERROR: Invalid ammount of arguments.\n");
		exit(0);
	}
	game.map = map_to_list(av[1]);
	good_input(&game);
	free_list(game.map);
	game.map = map_to_list(av[1]);
	init_values(&game);
	signal(SIGINT, signal_handler);
	g_game = &game;
	init_window(&game);
	return (0);
}
