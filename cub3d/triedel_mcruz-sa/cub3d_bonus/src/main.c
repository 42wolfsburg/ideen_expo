/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:46:32 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 15:10:53 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/* Exits printing `msg` */
void	errexit(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/* Parse dimension argument */
int	parse_args_dim(const char *s, t_vec *dim)
{
	dim->x = ft_atoi(s);
	s = ft_strchr(s, 'x');
	if (!s)
		return (ERR);
	dim->y = ft_atoi(s + 1);
	return (OK);
}

/* Parse arguments  */
int	parse_args(int argc, char *argv[], char **map, t_vec *dim)
{
	int		i;
	bool	has_map;
	bool	has_dim;

	has_map = false;
	has_dim = false;
	i = 0;
	while (++i < argc)
	{
		if (ft_endswith(argv[i], MAP_SUFFIX) && !has_map)
		{
			*map = argv[i];
			has_map = true;
		}
		else if (ft_strchr(argv[i], 'x') && !has_dim)
		{
			if (parse_args_dim(argv[i], dim) != OK)
				return (ERR);
			has_dim = true;
		}
		else
			return (ERR);
	}
	return (ft_ternary_int(argc < 3 || (has_map && has_dim), OK, ERR));
}

#ifndef TEST

int	main(int argc, char *argv[])
{
	t_game		game;
	t_vec		dim;
	char		*map;

	map = MAP_DEFAULT;
	dim = vec(GAME_W, GAME_H);
	if (argc != 2 || parse_args(argc, argv, &map, &dim) != OK)
		errexit("Usage: ./cub3D <mapfile>\n");
	game_init(&game, map, dim.x, dim.y);
	game_deinit(&game);
}

#endif
