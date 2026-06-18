/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:40:19 by robello           #+#    #+#             */
/*   Updated: 2026/01/08 22:40:19 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "get_next_line_bonus.h"
# include <libft.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define WIN_W				1600
# define WIN_H				900
# define ASPECT_RATIO		1.7778
# define MIN_W				640
# define MIN_H				360

# define FOV				0.66
# define MOVE_SPEED 		0.050
# define ROTA_SPEED 		0.041
# define MOUSE_SENS 		0.006

# define DOOR_SPEED			0.7
# define DOOR_OPEN_SPEED	0.7
# define DOOR_MAX_OPEN		0.95
# define DOOR_AUTO_CLOSE	5000

# define SPRITE_SCALE		0.6
# define PLAYER_HIT_RADIUS	0.05
# define PLAYER_RANGE		1.5
# define FLASH_TIME			11
# define SECRET_DOOR_NO		0
# define SECRET_DOOR_YES	1

# define COLL_RADIUS		0.3
# define MINIMAP_SCALE		5
# define MINIMAP_OFFSET_X	5
# define MINIMAP_OFFSET_Y	5

# define KEY_ESC			65307
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define KEY_LEFT			65363
# define KEY_RIGHT			65361
# define KEY_SPACE			32
# define KEY_42				61
# define KEY_ENTER			65293

# define WALL		'1'
# define FLOOR		'0'
# define DOOR		'D'
# define COLL		'C'
# define ENEMY		'X'
# define SECRET		'T'

# define ENE_FRAME	6
# define COLL_FRAME	7
# define DIFF_EASY	1
# define DIFF_MED	2
# define DIFF_HARD	3

# ifndef DIFFICULTY
#  define DIFFICULTY DIFF_EASY
# endif

# if DIFFICULTY == DIFF_EASY
#  define ENEMY_SPEED 0.005
# elif DIFFICULTY == DIFF_MED
#  define ENEMY_SPEED 0.008
# elif DIFFICULTY == DIFF_HARD
#  define ENEMY_SPEED 0.012
# endif

typedef enum e_keymask
{
	FWRD	= 1 << 0,
	BWRD	= 1 << 1,
	LEFT	= 1 << 2,
	RIGHT	= 1 << 3,
	TURN_L	= 1 << 4,
	TURN_R	= 1 << 5
}	t_keymask;

typedef struct s_input
{
	unsigned int	keys;
}	t_input;

typedef struct s_player
{
	char	start_char;
	int		raw_x;
	int		raw_y;
	double	play_x;
	double	play_y;
	double	playdir_x;
	double	playdir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rota_speed;
}	t_player;

typedef struct s_map
{
	char	**map;
	char	**raw_map;
	int		width;
	int		height;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		linen;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef enum e_text_id
{
	WALL_N,
	WALL_S,
	WALL_E,
	WALL_W,
	T_DOOR,
	T_SECRET_D,
	ENEMY_0,
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_5,
	COLL_0,
	COLL_1,
	COLL_2,
	COLL_3,
	COLL_4,
	COLL_5,
	COLL_6,
	G_OVER,
	Y_WIN,
	COUNT
}	t_text_id;

typedef struct s_tex_pack
{
	t_img	tex[COUNT];
}	t_txts;

typedef struct s_frame
{
	t_img	img;
}	t_frame;

typedef enum e_door
{
	CLOSED,
	OPENING,
	OPEN,
	CLOSING
}	t_door_st;

typedef struct s_door
{
	double		door_progress;
	int			door_x;
	int			door_y;
	int			is_secret;
	int			revealed;
	double		last_opened;
	t_door_st	state;
}	t_door;

typedef struct s_door_sys
{
	t_door	*list;
	int		count;
	int		secret_cnt;
	double	door_speed;
}	t_door_sys;

typedef struct s_bonus
{
	struct
	{
		int		enabled;
		double	radius;
	} s_collision;
	struct
	{
		int	enabled;
		int	scale;
		int	offset_x;
		int	offset_y;
	} s_minimap;
	struct
	{
		int		enabled;
		int		last_x;
		double	sensitivity;
	} s_mouse;
}	t_bonus;

typedef enum e_sprite_type
{
	SPRITE_COLL,
	SPRITE_ENE,
	SPRITE_DECOR
}	t_sprite_type;

typedef struct s_sprite
{
	double			sprite_x;
	double			sprite_y;
	double			dist;
	int				tex_id;
	t_sprite_type	type;
}	t_sprite;

typedef struct s_sprite_sys
{
	t_sprite	*list;
	int			count;
	int			zbuffer_w;
	double		*zbuffer;
}	t_sprite_sys;

typedef struct s_enemy
{
	double	ene_x;
	double	ene_y;
	double	spawn_x;
	double	spawn_y;
	double	enedir_x;
	double	enedir_y;
	double	ene_speed;
	int		alive;
	int		current_frame;
}	t_enemy;

typedef struct s_ene_sys
{
	t_enemy	*list;
	int		ene_count;
}	t_ene_sys;

typedef struct s_coll
{
	double	col_x;
	double	col_y;
	int		collected;
	int		current_frame;
}	t_coll;

typedef struct s_collect_sys
{
	t_coll	*list;
	int		total;
	int		collected;
}	t_coll_sys;

typedef enum e_gameover_state
{
	GAME_RUNNING,
	GAME_OVER,
	GAME_WIN,
	GAME_MENU
}	t_game_st;

typedef struct s_gameover
{
	t_game_st	state;
	t_img		overlay_img;
	int			fading;
}	t_gameover;

typedef struct s_sprite_cast
{
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_cast;

typedef struct s_ray
{
	double	wall_x;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		column_x;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		is_door;//
	int		door_idx;//
}	t_ray;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	double			game_time;
	int				flash;
	int				game_won;
	int				win_w;
	int				win_h;
	int				max_w;
	int				max_h;
	int				floor_color[3];
	int				ceiling_color[3];
	int				enemy_anim_frames;
	int				coll_anim_frames;
	int				res_choice;
	t_map			map;
	t_txts			tex;
	t_input			input;
	t_frame			frame;
	t_player		player;
	t_bonus			bonus;
	t_ene_sys		enemies;
	t_door_sys		doors;
	t_coll_sys		colls;
	t_gameover		gmover;
	t_sprite_sys	sprites;
}	t_game;

int		check_player_count(int count);
void	set_east_west_direction(t_game *game, char dir);
void	set_player_direction(t_game *game, char dir);
void	warn_high_resolution(int w, int h);

int		get_texture_x(t_game *game, t_ray *ray, t_img *tex);
int		get_pxl_color(t_img *img, int x, int y);
int		blend_color(int bg, int fg, float a);
void	draw_wall_column_alpha(t_game *game, t_ray *ray, int x, double a);
int		handle_keypress(int keycode, t_game *game);

t_img	*ft_select_wall_texture(t_game *game, t_ray *ray);
int		is_collected(t_game *game, int map_x, int map_y);
void	update_collectible_frames(t_game *game);
void	update_enemy_animation(t_game *game);
void	update_enemy_positions(t_game *game);

int		handle_window_close(t_game *game);
void	move_ray_x(t_ray *ray);
void	move_ray_y(t_ray *ray);
void	set_perp_dist(t_ray *ray);
double	calc_tex_pos(t_game *game, t_ray *ray, double step);

int		process_door_cell(t_game *game, t_ray *ray, int door_idx);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_step_and_side_dist(t_game *game, t_ray *ray);
void	ft_init_ray(t_game *game, t_ray *ray, int x);
void	ft_castrays(t_game *game);

void	draw_column_segment(t_game *game, t_ray *ray, t_img *tex, int tex_x);
int		ft_process_cell(t_game *game, t_ray *ray, char cell);
void	draw_wall_column(t_game *game, t_ray *ray, int x);
void	calculate_wall_texture(t_game *game, t_ray *ray);
void	calculate_wall_dimensions(t_game *game, t_ray *ray);

void	draw_collectible(t_game *game, int center_x, int center_y, int radius);
void	draw_wall_cell(t_game *game, int start_x, int start_y, int scale);
void	draw_floor_cell(t_game *game, int start_x, int start_y, int scale);
void	draw_cell(t_game *game, int map_x, int map_y);
void	draw_minimap(t_game *game);

void	ft_draw_arrow_tip(t_img *img, int x, int y, int color);
void	ft_draw_arrow_side(t_game *game, int cx, int cy, int side);
void	draw_walls(t_game *game);
void	draw_player(t_game *game);
void	render_minimap(t_game *game);

int		get_sprite_tex_x(t_sprite_cast *cast, int stripe, int tex_width);
void	draw_sprite_vertical(t_game *game, int data[4], t_img *tex,
			t_sprite_cast *cast);
void	draw_sprite_stripes(t_game *g, t_sprite *s,	t_sprite_cast *c,
			double ty);
void	calculate_sprite_cast(t_game *game, t_sprite_cast *cast, double tx,
			double ty);
void	draw_sprite_column(t_game *game, t_sprite *sprite,
			double tx, double ty);

void	prepare_collectibles(t_game *game);
void	prepare_enemies(t_game *game);
void	calculate_sprite_distances(t_game *game);
void	render_single_sprite(t_game *game, t_sprite *sprite);
void	render_sprites(t_game *game);

int		is_player_near_door(t_game *game, t_door *door);
void	sort_sprites(t_game *game);
int		create_rgb(int red, int green, int blue);
void	ft_put_pixel(t_img *img, int x, int y, int color);
void	draw_floor_ceiling(t_game *game);

void	draw_texture_centered(t_game *game, t_img *tex, float alpha);
void	draw_color_overlay(t_game *game, int color, float alpha);
void	draw_flash_overlay(t_game *game);
void	render_game_over(t_game *game);
void	render_win_fade(t_game *game);

int		is_player_in_range(t_game *game, double obj_x, double obj_y,
			double range);
void	check_single_collectible(t_game *game, t_coll *coll);
void	check_collectible_collisions(t_game *game);
void	check_single_enemy(t_game *game, t_enemy *ene);
void	check_enemy_collisions(t_game *game);

int		get_door_tex_x(t_game *game, t_ray *ray, t_img *tex);
int		check_cell_for_door(t_game *game, int map_x, int map_y);
void	handle_door_hit(t_game *game, t_ray *ray, int door_idx);
void	check_hit_type(t_game *game, t_ray *ray, char cell);
t_img	*select_door_texture(t_game *game, t_ray *ray);

int		handle_keyrelease(int keycode, t_game *game);
int		handle_window_close(t_game *game);
int		handle_mouse_move(int x, int y, t_game *game);
void	ft_setup_hooks(t_game *game);
int		create_game_window(t_game *game);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		find_door_at_position(t_game *game, int map_x, int map_y);
void	check_door_interaction(t_game *game, int dx, int dy);
int		check_door_at_offset(t_game *game, int dx, int dy);
void	check_nearby_doors(t_game *game);

void	show_resolution_menu(t_game *game);
int		get_confirmation(void);
void	set_high_medium_speeds(t_game *game);
void	set_low_speeds(t_game *game);
void	set_speeds_for_resolution(t_game *game);

int		resolution_fits_screen(t_game *game, int w, int h);
int		get_user_choice(void);
void	set_resolution_from_choice(t_game *game, int choice);
void	detect_screen_size(t_game *game);
void	setup_window_resolution(t_game *game);

int		check_door_collision(t_door *door, double x, double y);
int		collision_point(t_game *game, double x, double y);
int		ft_check_collision(t_game *game, double new_x, double new_y);
void	rotate_right(t_game *game);
void	handle_movement(t_game *game);

void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);

void	ft_render_frame(t_game *game);
double	get_current_time(void);
void	check_entity_collisions(t_game *game);
void	ft_update_running_game(t_game *game, double delta_time);
int		game_loop(t_game *game);

void	update_door_animation(t_door *door, double delta_time);
void	check_door_auto_close(t_door *door, double curr_time);
void	check_secret_door_revel(t_game *game, t_door *door);
void	update_doors(t_game *game, double delta_time);
void	interact_with_door(t_game *game, int idx);

void	fill_coll_enemy_cell(t_game *game, int x, int y, int indices[2]);
void	fill_door_cell(t_game *game, int x, int y, int *door_idx);
void	fill_bonus_entities(t_game *game);
void	allocate_sprite_list(t_game *game);
int		allocate_bonus_entities(t_game *game);

void	debug_texture_loading(t_game *game);
int		setup_bonus_entities(t_game *game);
int		load_enemy_textures(t_game *game);
int		load_door_textures(t_game *game);
int		main_load_bonus_textures(t_game *game);

t_img	load_tx(void *mlx, char *path);
int		load_game_over_win_textures(t_game *game);
int		load_single_collectible_texture(t_game *game, int i);
int		load_collectible_textures(t_game *game);
int		load_single_enemy_texture(t_game *game, int i);

void	free_strings(char **array);
int		cleanup_on_error(char *clean, char *line, int is_first);
int		cleanup_and_return(char **padded, char **processed, int ret_val);
int		cleanup_padded(char **padded);
int		cleanup_both(char **padded, char **processed);

void	print_reachable_map_debug(char **map, char **reachable, int dims[2]);
void	print_char_error(char c, int file_line, int col);
void	print_empty_line_error(int file_line, int is_first);
void	print_map_error(char *reason);
void	print_header_error(char *line, int line_num, char *reason);

void	print_unreachable_error(int i, int j, char c);
void	print_row_chars(char *row);
void	print_map_debug(char **map, const char *label);
void	print_map(char **map);
void	print_escaped_line(char *line);

void	ft_check_victory(t_game *game);
void	set_west_direction(t_game *game);
void	init_player_direction(t_game *game);
void	ft_reset_game_enemies_and_state(t_game *game);
void	ft_reset_game(t_game *game);

int		check_player_count(int count);
void	set_east_west_direction(t_game *game, char dir);
void	set_player_direction(t_game *game, char dir);

void	ft_cleanup_lists(t_game *game);
void	ft_cleanup_textures(t_game *game);
void	ft_cleanup_game(t_game *game);

int		is_unreachable_entity(char c);
int		check_unreachable_entities(char **map, char **reachable, int dims[2]);
void	finalize_map_processing(t_game *game, char **padded, char **processed);
void	flood_fill(char **map, int pos[2], char fill_char, char target_char);
void	flood_fill_walkable(char **map, int pos[2], char fill_char,
			int dims[2]);

char	*pad_line_to_width(char *line, int target_width);
char	**pad_map_lines(char **map, int height, int max_width);
char	**pad_map_to_rectangle(char **map);
int		check_cell_enclosure(char **map, int pos[2], int dims[2]);
int		validate_map_enclosure(char **map);

int		validate_player_and_entities_reachable(char **map, int player_pos[2]);
int		count_bonus_entities(t_game *game, char c, int x, int y);
int		validate_single_char(t_game *g, int val_data[4], char c,
			int *player_cnt);
int		validate_all_chars(t_game *g, char *line, int line_data[3],
			int *player_cnt);
int		validate_entity_counts(t_game *game);

int		is_map_character(char c);
int		is_map_char(char c);
char	**copy_map_for_flood_fill(char **map, int height);
char	**ft_copy_map(char **map, int height);
int		check_map_cells(char **map, int h, int w);

void	ft_mark_edges_horizontal(char **temp, int h, int w);
void	ft_mark_edges_vertical(char **temp, int h, int w);
char	**mark_edge_spaces_as_void(char **map);
void	convert_void_to_floor(char **result, char **void_map, int height);
char	**convert_interior_spaces_to_floor(char **map);

int		process_first_line(t_game *game, char *line, int file_line,
			int *player_cnt);
char	**add_line(char **map, char *line, int size);
int		process_any_line(t_game *game, char *line, int file_line, int data[2]);
int		process_next_line(t_game *game, char *line, int file_line,
			int *player_cnt);
int		validate_all_headers(t_game *game);

int		parse_and_validate_map(int fd, t_game *game, char *first_line,
			int line_num);
char	*find_first_map_line(int fd, int *line_num);
int		parse_raw_map(t_game *game, int fd, char *first_line, int start_line);
int		find_max_width(char **map);
int		process_and_validate_map(t_game *game);

int		is_empty(char *s);
int		ft_isdigit_str(char *str);
void	set_color(int rgb[3], int target[3]);
int		ft_parse_rgb(char **rgb_str, int rgb[3]);
int		apply_valid_color(t_game *game, char **rgb_str, int rgb[3],
			int is_floor);

int		ft_is_space(char c);
int		ft_validate_texture_header(char *trimmed);
int		ft_validate_color_header(char *trimmed);
int		parse_texture_path(t_game *game, char *line, t_text_id tex_id);
int		parse_and_count(t_game *game, char *trimmed, int tex_id, int *count);

char	*remove_carriage_returns(char *str);
int		validate_header_format(char *trimmed);
int		check_if_map_line(char *trimmed);
int		parse_color(t_game *game, char *line, int is_floor);
int		process_header_line(t_game *game, char *trimmed, int *headers_found);

int		handle_map_start(char *line, int *line_num, int *headers_found);
int		parse_cub_header(t_game *game, char *line, int *headers_found);
int		is_empty_line(char *s);
int		reject_tabs_in_line(char *line, int line_num);
int		process_header_line_wrapper(t_game *game, char *line, int *line_num,
			int *headers_found);

int		parse_all_headers(int fd, t_game *game, char **first_line,
			int *line_num);
int		parse_cub_file(int fd, t_game *game);
int		validate_input(char **av);
void	ft_init_colors(t_game *game);
void	ft_init_systems_struct(t_game *game);

void	ft_init_game_struct(t_game *game);
void	ft_display_game_info(t_game *game);
int		ft_init_graphics(t_game *game);
int		ft_init_mlx_and_parse(t_game *game, int fd);
int		main(int ac, char **av);

#endif
