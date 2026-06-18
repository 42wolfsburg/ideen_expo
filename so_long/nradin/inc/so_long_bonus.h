/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:03 by nradin            #+#    #+#             */
/*   Updated: 2023/03/04 12:52:43 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <limits.h>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>

# define WALL           '1'
# define FLOOR          '0'
# define COLLECTIBLE    'C'
# define PLAYER         'P'
# define MAP_EXIT       'E'
# define ENEMY_VERTICAL 'V'
# define ENEMY_HORIZONTAL 'H'

# define WALL_PATH "sprites/wall.png"
# define FLOOR_PATH "sprites/floor.png"
# define COLLECTIBLE_PATH "sprites/gryvnya.png"
# define PLAYER_UP_0_PATH "sprites/devil_up.png"
# define PLAYER_UP_1_PATH "sprites/devil_up_1.png"
# define PLAYER_UP_2_PATH "sprites/devil_up_2.png"
# define PLAYER_DOWN_0_PATH "sprites/devil_down.png"
# define PLAYER_DOWN_1_PATH "sprites/devil_down_1.png"
# define PLAYER_DOWN_2_PATH "sprites/devil_down_2.png"
# define PLAYER_LEFT_0_PATH "sprites/devil_left.png"
# define PLAYER_LEFT_1_PATH "sprites/devil_left_1.png"
# define PLAYER_LEFT_2_PATH "sprites/devil_left_2.png"
# define PLAYER_RIGHT_0_PATH "sprites/devil_right.png"
# define PLAYER_RIGHT_1_PATH "sprites/devil_right_1.png"
# define PLAYER_RIGHT_2_PATH "sprites/devil_right_2.png"
# define PLAYER_WIN_PATH "sprites/devil_win.png"
# define PLAYER_LOOSE_PATH "sprites/devil_loose.png"
# define ENEMY_1_UP_0_PATH "sprites/cossack_1_up.png"
# define ENEMY_1_UP_1_PATH "sprites/cossack_1_up_1.png"
# define ENEMY_1_UP_2_PATH "sprites/cossack_1_up_2.png"
# define ENEMY_1_DOWN_0_PATH "sprites/cossack_1_down.png"
# define ENEMY_1_DOWN_1_PATH "sprites/cossack_1_down_1.png"
# define ENEMY_1_DOWN_2_PATH "sprites/cossack_1_down_2.png"
# define ENEMY_1_LEFT_0_PATH "sprites/cossack_1_left.png"
# define ENEMY_1_LEFT_1_PATH "sprites/cossack_1_left_1.png"
# define ENEMY_1_LEFT_2_PATH "sprites/cossack_1_left_2.png"
# define ENEMY_1_RIGHT_0_PATH "sprites/cossack_1_right.png"
# define ENEMY_1_RIGHT_1_PATH "sprites/cossack_1_right_1.png"
# define ENEMY_1_RIGHT_2_PATH "sprites/cossack_1_right_2.png"
# define ENEMY_2_UP_0_PATH "sprites/cossack_2_up.png"
# define ENEMY_2_UP_1_PATH "sprites/cossack_2_up_1.png"
# define ENEMY_2_UP_2_PATH "sprites/cossack_2_up_2.png"
# define ENEMY_2_DOWN_0_PATH "sprites/cossack_2_down.png"
# define ENEMY_2_DOWN_1_PATH "sprites/cossack_2_down_1.png"
# define ENEMY_2_DOWN_2_PATH "sprites/cossack_2_down_2.png"
# define ENEMY_2_LEFT_0_PATH "sprites/cossack_2_left.png"
# define ENEMY_2_LEFT_1_PATH "sprites/cossack_2_left_1.png"
# define ENEMY_2_LEFT_2_PATH "sprites/cossack_2_left_2.png"
# define ENEMY_2_RIGHT_0_PATH "sprites/cossack_2_right.png"
# define ENEMY_2_RIGHT_1_PATH "sprites/cossack_2_right_1.png"
# define ENEMY_2_RIGHT_2_PATH "sprites/cossack_2_right_2.png"
# define MAP_EXIT_0_PATH "sprites/exit_0.png"
# define MAP_EXIT_1_PATH "sprites/exit_1.png"
# define MAP_EXIT_2_PATH "sprites/exit_2.png"
# define MAP_EXIT_3_PATH "sprites/exit_3.png"
# define MAP_EXIT_4_PATH "sprites/exit_4.png"
# define SHADOW_PATH "sprites/shadow.png"
# define SHADOW_COIN_PATH "sprites/shadow_coin.png"
# define BLACK_PATH "sprites/black.png"

# define ARGS_ERROR "Wrong amount of arguments!\n"
# define FILE_ERROR "Given file path is invalid!\n"
# define MAP_RECT_ERROR "Map is not rectangular!\n"
# define MAP_WALL_ERROR "Map is not surrounded by walls!\n"
# define MAP_PATH_ERROR "Map has no valid path!\n"
# define MAP_COMPONENTS_ERROR "Map has has wrong amount of \
components (exit/player/collectibles)!\n"
# define MAP_INVALID_CHARACTERS_ERROR "Map has some invalid characters!\n"
# define SPRITE_ERROR "Couldn't find a sprite. Does it exist?\n"
# define MLX_INIT_ERROR "MLX initialization failed!\n"

# define KEY_W           MLX_KEY_W
# define KEY_A           MLX_KEY_A
# define KEY_S           MLX_KEY_S
# define KEY_D           MLX_KEY_D
# define KEY_ESC         MLX_KEY_ESCAPE

typedef struct s_comp
{
    int exit;
    int player;
    int collect;
    int enemy;
}   t_comp;

typedef struct s_being
{
    int         x;
    int         y;
    int         offset_x;
    int         offset_y;
    int         last_move;
    int         type;
}   t_being;

typedef struct s_image
{
    mlx_image_t *img;
    int         x;
    int         y;
}   t_image;

typedef struct s_game
{
    int             win_condition;
    int             movements;
    int             enemy_count;
    int             frame;
    int             map_x;
    int             map_y;
    mlx_t           *mlx;
    char            **map;
    long long       time;
    t_being         player_status;
    t_being         *enemy_status;
    t_image         enemy[2][4][5];
    t_image         player[4][5];
    t_image         player_win;
    t_image         player_loose;
    t_image         wall;
    t_image         floor;
    t_image         collectible;
    t_image         map_exit[5];
    t_image         win_screen;
    t_image         shadow;
    t_image         shadow_coin;
    t_image         black;
    t_image         display_buffer;
    t_image         draw_buffer;
}   t_game;

typedef struct s_point
{
    int     x;
    int     y;
    int     dist;
}   t_point;

size_t      ft_strstr_len(char **str);
void        init_comp(t_comp *comps);
void        throw_error(t_game *game, t_comp *comps, char *message);
char        **ft_strstrdup(char **str, int size);
void        ft_strstr_free(char **str);

int         count_lines(int fd);
char        **read_map(t_game *game, char    *map);
int         check_rectangular(char **map);
int         check_walls(char **map);
int         components_ifs(char c, t_comp *comps);
t_comp      *check_components(t_game *game, char **map);
void        count_components(t_game *game, char **map, t_comp *comps);
int         compare_components(t_comp *comps1, t_comp *comps2);
void        check_path(char **map, t_comp *comps, int x, int y);
int         find_path(t_game *game, t_comp *comps);
void        check_map(t_game *game);

int         create_trgb(int t, int r, int g, int b);
int         get_t(int trgb);
int         get_r(int trgb);
int         get_g(int trgb);
int         get_b(int trgb);

int         ft_abs(int n);
int         calc_off(int offset);
int         check_move(int *offset, int *coord);
int         move_enemies(t_game *game);
int         check_direction(t_being *being);
void        redraw_backgroung(t_game *game);
void        redraw_being_backgroung(t_game *game, t_being *being);
int         init_enemies(t_game *game);

void        game_init(t_game *game);
void 		game_loop(void *param);
void        check_interaction(t_game *game, t_being being);
int         check_win(t_game *game);
int         check_enemies(t_game *game, int x, int y);
int         check_player(t_game *game, int x, int y);
void        moves_ifs(int key, int *x, int *y, t_being *being);

int         init_images(t_game    *game);
void        pick_image(char comp, t_game *game, int x, int y);
void        render_image(t_game *game, t_image sprite, int x, int y);
void        render_map(t_game *game, char **map);
void        render_exit(t_game *game);
void        render_coins(t_game *game);
void        render_animations(t_game *game);
void        render_player(t_game *game, t_being *player);
void        render_player_loose(t_game *game);
void        render_player_win(t_game *game);
void        render_enemy(t_game *game, t_being *enemy);
mlx_image_t *show_moves(t_game *game);
long long   millitimestamp(void);
void        copy_image_to_buffer(mlx_image_t *dest, mlx_image_t *src, int dest_x, int dest_y);
void        clear_buffer(mlx_image_t *buffer, uint32_t color);

void		key_hook(mlx_key_data_t keydata, void *param);
void        update_player_pos(t_game *game);

void        free_game(t_game *game);
void 		close_game(void *param);
void        game_win(t_game *game);
void        game_loose(t_game *game);
void        game_end(t_game *game);
void        free_game(t_game *game);

#endif
