/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:42:43 by jastomme          #+#    #+#             */
/*   Updated: 2026/05/13 10:40:26 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <X11/X.h>
# include <mlx.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include <signal.h>
# define TILE_SIZE 120
# define TXT_WALL "textures/4wall.xpm"
# define TXT_C "textures/1collectible.xpm"
# define TXT_GRD "textures/3background.xpm"
# define TXT_EX_C "textures/5exit_closed.xpm"
# define TXT_EX_O "textures/2exit_open.xpm"
# define TXT_P "textures/0player.xpm"
# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img[6];
	t_map	*map;
	int		p_count;
	int		e_count;
	int		c_count;
	int		player_x;
	int		player_y;
	int		collected;
	int		player_direction;
	int		steps;
}			t_game;

//check_utils.c
int		is_wall_line(const char *line, size_t width);
char	get_char_at(t_map *head, size_t row, size_t col);
void	set_char_at(t_map *head, size_t row, size_t col, char new_char);
void	flood_fill(t_map *head, size_t x, size_t y);
void	get_map_dimensions(t_map *head, size_t *width, size_t *height);

//checking_it.c
int		is_rectangular(t_game *game);
int		closed_walls(t_game *game);
int		check_elements(t_game *game);
int		only_valid_elements(t_game *game);
int		path_is_valid(t_game *game);

//freeing_it.c
void	free_list(t_map *head);
int		exit_game(t_game *game, char *str);
void	input_exit(t_game *game, char *str);

//initialise.c
void	init_textures(t_game *game);
void	render_map(t_game *game);
void	init_window(t_game *game);
void	render_textures(char target, t_game *game, int x, int y);
void	init_values(t_game *game);

//key_hooks.c
int		close_game(t_game *game);
int		key_hook(int keycode, t_game *game);
void	setup_hooks(t_game *game);
void	signal_handler(int sig);

//main.c
void	good_input(t_game *game);

//moving_it.c
t_map	*get_target_pos(t_map *map, int target_y);
void	player_events(t_game *game, char target_tile);
void	update_p_pos(t_game *game, t_map *old_pos, int new_x, int new_y);
void	move_player(t_game *game, int dx, int dy);

//terminal_it.c
void	game_over(t_game *game);
void	you_won(t_game *game);
void	no_exit(void);
void	render_steps(t_game *game);

//utils.c
t_map	*create_node(char *line);
void	append_node(t_map **head, t_map *new_node);
void	find_player_pos(t_game *game);
int		check_unreachable(t_map *head);

#endif
