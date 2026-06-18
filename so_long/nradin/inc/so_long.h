/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:03 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 12:43:03 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>

# define WALL				'1'
# define FLOOR				'0'
# define COLLECTIBLE		'C'
# define PLAYER				'P'
# define MAP_EXIT			'E'
# define ENEMY_VERTICAL		'V'
# define ENEMY_HORIZONTAL	'H'

# define WALL_PATH "sprites/wall.xpm"
# define FLOOR_PATH "sprites/floor.xpm"
# define COLLECTIBLE_PATH "sprites/gryvnya.xpm"
# define PLAYER_PATH "sprites/devil_down.xpm"
# define PLAYER_WIN_PATH "sprites/devil_win.xpm"
# define MAP_EXIT_PATH "sprites/exit_0.xpm"

# define ARGS_ERROR "Wrong amount of arguments!\n"
# define FILE_ERROR "Given file path is invalid!\n"
# define MAP_RECT_ERROR "Map is not rectangular!\n"
# define MAP_WALL_ERROR "Map is not surrounded by walls!\n"
# define MAP_PATH_ERROR "Map has no valid path!\n"
# define MAP_COMPONENTS_ERROR "Map has has wrong amount of \
components (exit/player/collectibles)!\n"
# define MAP_INVALID_CHARACTERS_ERROR "Map has some invalid characters!\n"
# define MAP_BONUS_ERROR "Bonus map uses enemies. Run make bonus first.\n"
# define SPRITE_ERROR "Couldn't find a sprite. Does it exist?\n"

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define KEY_ESC			65307

typedef struct s_comp
{
	int	exit;
	int	player;
	int	collect;
}	t_comp;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_coords
{
	int		x;
	int		y;
}	t_coords;

typedef struct s_game
{
	int			win_condition;
	int			movements;
	int			map_x;
	int			map_y;
	void		*mlx;
	void		*win;
	char		**map;
	t_coords	player_pos;
	t_image		player;
	t_image		player_win;
	t_image		wall;
	t_image		floor;
	t_image		collectible;
	t_image		map_exit;
}	t_game;

typedef struct s_point
{
	int		x;
	int		y;
	int		dist;
}	t_point;

size_t	ft_strstr_len(char **str);
void	init_comp(t_comp *comps);
void	throw_error(t_game *game, t_comp *comps, char *message);
char	**ft_strstrdup(char **str, int size);
void	ft_strstr_free(char **str);
void	free_game(t_game *game);

int		count_lines(int fd);
char	**read_map(t_game *game, char *map);
int		check_rectangular(char **map);
int		check_walls(char **map);
int		components_ifs(char c, t_comp *comps);
t_comp	*check_components(t_game *game, char **map);
void	count_components(t_game *game, char **map, t_comp *comps);
int		compare_components(t_comp *comps1, t_comp *comps2);
void	check_path(char **map, t_comp *comps, int x, int y);
int		find_path(t_game *game, t_comp *comps);
void	check_map(t_game *game);

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

int		game_loop(t_game *game);
void	game_init(t_game *game);
int		init_images(t_game	*game);
void	render_image(t_game *game, t_image sprite, int x, int y);
void	pick_image(char comp, t_game *game, int x, int y);
void	render_map(t_game *game, char **map);

int		key_hook(int keycode, t_game *game);

int		close_game(t_game *game);
void	game_win(t_game *game);

#endif
