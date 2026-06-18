/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:09:56 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 15:18:50 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// \file
#ifndef CUB_H
# define CUB_H

# include <libft.h>
# include "vector.h"

# include <X11/X.h>
# include <X11/keysym.h>

# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# include <mlx.h>

# include <assert.h>

# include <math.h>

# include <math.h>
# include <stdbool.h>

# include "config.h"

# include "error.h"

# define DEG			0.017453292519943295
# define GRID_WALL		0

# define OK				0
# define ERR			-1

// textures
# define TXTNORTH		DNORTH
# define TXTEAST		DEAST
# define TXTSOUTH		DSOUTH
# define TXTWEST		DWEST
# define TXTAGENT0		4
# define TXTAGENT1		5
# define TXTAGENT2		6
# define TXTPILL		7
# define TXTDOOR		8
# define TXTPHONEBOX0	9
# define TXTPHONEBOX1	10
# define TXTPOINT		11
# define TXTGUN			12
# define TXTBOX			13
# define TXTFONT		14
# define TXTBULLET		15
# define TXTFLOOR		16
# define TXTMAX			TXTFLOOR

typedef struct s_obj	t_obj;

# define CHARS_WALKABLE	"0NEWSRPDA"
# define CHARS_BLOCKING	"123456789"

# define FONT_CHAR_W	15
# define FONT_CHAR_H	30
# define MATTEX_FONT_H	24

# define INPUT_STATE_SIZE	65535

struct s_linestate
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;
	int	steps;
	int	i;
};

typedef struct s_floor
{
	int	red;
	int	green;
	int	blue;
}	t_floor;

typedef struct s_ceil
{
	int	red;
	int	green;
	int	blue;
}	t_ceil;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
	int		spawn_x;
	int		spawn_y;
	int		txtcount;
	int		objcount;
	int		introcount;
	char	direction;
	char	**map_textures;
	char	**intro_phrases;
	char	*level;
	t_obj	*obj;
	t_floor	floor_color;
	t_ceil	ceil_color;
	t_color	floor;
	t_color	ceiling;
	int		txt_index;
	int		intro_index;
}	t_map;

/// image type containing image metadata as well as the mlx image pointer
typedef struct s_img
{
	// metadata
	int				width;
	int				height;
	// mlx data
	void			*mlximg;
	unsigned char	*data;
	int				bpp;
	int				size_line;
	int				endian;
	float			scale;
}	t_img;

/// image section (image pointer + rect)
typedef struct s_imgsec
{
	t_img	*img;
	t_rect	sec;
}	t_imgsec;

/// game display
typedef struct s_display
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	buffer;
}	t_display;

typedef enum e_objtype
{
	OBJ_NONE = 0,
	OBJ_AGENT,
	OBJ_PILL,
	OBJ_PHONEBOX,
	OBJ_PLAYER,
	OBJ_PLANE,
	OBJ_BULLET,
	OBJ_DOOR,
}	t_objtype;

typedef struct s_bullet
{
	t_pt3	speed;
}	t_bullet;

typedef struct s_enemy
{
	unsigned int	hit_points;
}	t_enemy;

typedef enum e_doorstate
{
	D_OPEN,
	D_OPENING,
	D_CLOSED,
	D_CLOSING
}	t_doorstate;

typedef struct s_door
{
	int			open;
	t_doorstate	state;
}	t_door;

/// game object: one of several types of game entities
/// that are rendered separately from the walls
typedef struct s_obj
{
	t_objtype	type;
	t_pt3		pos;
	float		width;
	float		height;
	float		rot;
	t_vec		normal;
	int			texture_id;
	union
	{
		t_bullet	bullet;
		t_enemy		enemy;
		t_door		door;
	}	u_obj;
}	t_obj;

// hit record struct
// when we detect a ray hit, the function returns
// this information
typedef struct s_hitrec
{
	t_obj	*obj;	// obj that was hit - can be WALL (=NULL)
	float	r;		// position along orthogonal line
	float	dist;	// map distance (2D) from camera
	t_pt	hit;	// position where ray hits
	t_vec	normal;	// normal vector
}	t_hitrec;

// column data for one rendering single column
typedef struct s_column_data
{
	t_line		ray;
	t_hitrec	hitlist[MAXHITS + 1];
}	t_column_data;

/// Animated matrix texture
typedef struct s_mattex
{
	t_pt2	pts[MATTEX_SYMS];
	char	*data;
	int		datalen;
}	t_mattex;

/// Threadinfo type - contains information passed to a render thread
typedef struct s_tinfo
{
	struct s_game	*game;
	int				thread_id;
}	t_threadinfo;

typedef struct s_textinfo
{
	char	*text;
	t_color	color;
	int		pos;
	bool	carret;
}	t_textinfo;

typedef struct s_raymarch
{
	t_pt		pvert;
	t_pt		phor;
	float		nxt_dist_vert;
	float		nxt_dist_hor;
	float		step_vert;
	float		step_hor;
	float		stepx;
	float		stepy;
	int			dx;
	int			dy;
	t_hitrec	hit;
}	t_raymarch;

typedef enum e_gamestate
{
	S_OVER = 0,
	S_INTRO,
	S_RUNNING,
	S_PAUSING,
	S_PAUSED,
	S_WON,
}	t_gamestate;

/// game struct, containing complete game state and assets
typedef struct s_game
{
	t_display		disp;
	// game state
	t_gamestate		state;
	unsigned int	ticks;
	t_vec3			pos;
	float			mz;
	float			rot;
	float			rotx;
	float			health;
	bool			damage_taken;
	// game objects
	t_obj			objects[MAX_OBJECTS];
	// input
	unsigned char	input_state[INPUT_STATE_SIZE];
	// map
	t_map			map;
	//minimap
	t_rect			minimap_rect;
	t_ipt			minimap_center;
	// graphics
	float			fov;
	float			fstop;
	float			cam_width;
	float			cam_height;
	int				upscale;
	struct timeval	last_draw;
	int				fps;
	// textures
	t_img			*textures;
	// matrix mode
	int				matrix_mode;
	float			matrix_mode_mix;
	t_mattex		mt;
	t_img			mattex;
	// toggleables
	bool			physics;
	bool			show_minimap;
	bool			show_debug;
	// multi-threaded rendering
	t_column_data	*hit_buffer;
	pthread_mutex_t	mutex_render;
	int				next_col;
	pthread_t		threads[THREADS];
	t_threadinfo	threadinfos[THREADS];
	pthread_t		thread_music;
}	t_game;

/* src/color.c */
t_color			col_lum(t_color c, float f);
t_color			col_fade(t_color color, float dist);
t_color			col_mix(t_color a, t_color b, float mix);
t_color			col_apply(t_color col_orig, t_color col_apply);
/* src/display.c */
void			display_init(t_display *disp, int w, int h);
void			display_deinit(t_display *disp);
void			display_update(t_display *disp);
/* src/hitlist.c */
t_hitrec		hitnone(void);
void			hitrec_print(t_hitrec *hr);
void			hitlist_print(t_hitrec *hr);
void			hitlist_sort(t_hitrec *hitlist);
/* src/input.c */
bool			game_key_pressed(t_game *game, int kc);
void			game_set_key(t_game *game, int kc, int state);
/* src/main.c */
void			errexit(char *msg);
int				parse_args_dim(const char *s, t_vec *dim);
int				parse_args(int argc, char *argv[], char **map, t_vec *dim);
int				main(int argc, char *argv[]);
/* src/matrix_texture.c */
int				mattex_init(t_mattex *m);
void			mattex_update(t_mattex *m);
char			random_char(t_mattex *mt, int col);
void			mattex_draw(t_mattex *m, t_game *game, t_img *img);
/* src/raycast.c */
float			pt_dist(const t_pt *p1, const t_pt *p2);
float			pt3_dist(const t_pt3 *p1, const t_pt3 *p2);
t_vec			vec_swap(t_vec v);
t_hitrec		line_inters_line(const t_line *l1, const t_line *l2);
t_pt			map_nxt_vert(t_map *map, t_line *l);
t_pt			map_nxt_hor(t_map *map, t_line *l);
t_hitrec		map_ray_intersect(t_map *map, t_line *l);
/* src/raymarch.c */
bool			raymarch_horizontal(t_map *map, t_line *l, t_raymarch *rm);
bool			raymarch_vertical(t_map *map, t_line *l, t_raymarch *rm);
void			raymarch_init(t_raymarch *rm, t_map *map, t_line *l);
t_pt			map_nxt_vert(t_map *map, t_line *l);
t_pt			map_nxt_hor(t_map *map, t_line *l);
/* src/sound.c */
void			*sound_play(void *args);
/* src/test.c */
/* src/game/game.c */
void			game_calc_camera_params(t_game *game);
void			game_rot(t_game *game, float diff);
bool			game_collides(t_game *game, t_vec3 pos);
bool			game_check_object_collisions(t_game *game, t_vec3 pos);
void			game_move(t_game *game, t_vec *dir);
void			game_obj_takedamage(t_obj *o, int dmg);
bool			game_collides_obj(t_game *game, t_obj *obj);

void			game_update_objects(t_game *game);
void			game_update_door_object(t_game *game, int *i);
void			game_update_matrix_agent(t_game *game, t_pt objpos,
					t_pt pos, int *i);
void			game_update_bullet(t_game *game, int *i);
void			game_update_pill(t_game *game, t_pt objpos, t_pt pos, int *i);
void			game_update_phonebox(t_game *game, int *i);
void			game_handle_mouse_input(t_game *game);
void			game_update_physics(t_game *game);
void			game_update_walk(t_game *game);
void			game_update_move(t_game *game);
void			game_update_matrix(t_game *game);
void			game_update(t_game *game);
t_line			game_ray_cast(t_game *game, float f);
void			game_framectrl(t_game *game, struct timeval *now,
					struct timeval *then);
int				game_loop(t_game *game);
/* src/game/game_actions.c */
void			game_shoot(t_game *game);
void			game_setblock(t_game *game);
void			game_unsetblock(t_game *game);
void			game_interact(t_game *game);
void			game_pause_toggle(t_game *game);
/* src/game/game_init.c */
void			game_map_add_planes(t_game *game);
void			game_init_hooks(t_game *game);
void			game_init_map(t_game *game, char *map_path);
void			game_txt_load(t_game *game, int txtid, char *path);
void			game_init(t_game *game, char *map_path, int w, int h);
/* src/game/game_deinit.c */
void			game_deinit(t_game *game);
void			game_deinit_textures(t_game *game);
int				game_handle_close(void *param);
void			game_setup_window_close_handler(void *win_ptr);
/* src/game/game_init_textures.c */
void			game_obj_new(t_game *game, t_objtype type, t_vec3 *pos);
void			game_obj_door_init(t_game *game, t_obj *nobj, t_vec3 *pos);
int				game_init_textures(t_game *game);
void			game_init_img_textures(t_game *game);
void			game_map_add_objects(t_game *game);
/* src/game/game_init_utils.c */
void			game_obj_print(t_obj *obj);
void			game_init_logic(t_game *game);
void			game_init_camera(t_game *game);
t_objtype		map_char_to_objtype(char objchar);
void			game_initialize_minimap_variables(t_game *game);
/* src/game/game_input.c */
int				game_mousedown(int key, int x, int y, t_game *game);
void			game_keydown_controls(t_game *game, int key);
int				game_keydown(int key, t_game *game);
int				game_keyup(int key, t_game *game);
/* src/game/game_mouse.c */
void			game_mouse_trap(t_game *game);
void			game_mouse_release(t_game *game);
/* src/game/game_object.c */
void			game_obj_add(t_game *game, t_obj *obj);
t_pt			mapwall_get_coord(int dir, t_pt3 *wcoord);
t_hitrec		game_obj_intersect(t_game *game, t_obj *obj, const t_line *ray);
t_color			wall_get_pixel(t_game *game, t_hitrec *hit, float z, int *past);
t_color			obj_get_pixel(t_game *game, t_hitrec *hit, float z, int *past);
t_color			obj_get_pixel_bullet(t_game *game, t_hitrec *hit, float *z);
t_color			obj_get_pixel_plane(t_game *game, t_hitrec *hit,
					float *z, int *past);
t_color			obj_get_pixel_phonebox(t_game *game, t_hitrec *hit, float *z);
t_color			obj_get_pixel_pill(t_game *game, t_hitrec *hit, float *z);
t_color			obj_get_pixel_agent(t_game *game, t_hitrec *hit,
					float *z, int *past);
t_color			obj_get_pixel_door(t_game *game, t_hitrec *hit,
					float *z, int *past);
t_img			*obj_get_agent_texture(t_game *game);
/* src/game/game_ray.c */
void			game_get_2d_hits(t_game *game, t_hitrec *hitlist, t_line ray);
/* src/game/game_render.c */
float			cam_coord_to_z(t_game *game,
					float dist, float cam_y, float fstop_diag);
void			*game_render_thread(void *arg);
void			game_render_prep_col(t_game *game, int x, int w);
t_color			game_render_floor_ceil(t_game *game,
					int x, float z, t_vec diag_camy);
t_color			game_render_ceil(t_game *game, int bufpos, t_pt campos,
					float fstop_diag);
void			game_render_col(t_game *game, int x, int w);
t_color			game_render_minimap_pxl(t_game *game, int x, int y);
void			game_draw_minimap_direction(t_game *game);
void			game_draw_crosshairs(t_game *game);
void			game_draw_intro(t_game *game);
void			game_draw_frame(t_game *game);
void			game_draw_overlay_txt(t_game *game, char *msg);
void			game_render_multi(t_game *game);
void			game_render(t_game *game);
void			game_draw(t_game *game);
/* src/game/game_hooks.c */
void			game_expose(t_game *game);
/* src/map/map.c */
void			map_read(t_map *map, char *path);
char			*map_read_header(t_map *map, int fd, int *in_header);
void			map_read_body(t_map *map, int fd, char *line);
int				map_last_new_line(char *line);
/* src/map/map_squares.c */
bool			map_inrange(t_map *map, int x, int y);
char			map_get(t_map *map, int x, int y);
void			map_set(t_map *map, int x, int y, char c);
/* src/map/map_allocation.c */
void			map_grid_allocation(t_map *map, char *path);
void			map_obj_allocation(t_map *map);
void			map_init_map_obj(t_map *map, int index);
char			**map_calloc(t_map *map);
char			**map_copy_allocation(t_map *map);
/* src/map/map_checks.c */
int				map_metadata_complete(t_map *map);
void			map_validation(t_map *map);
int				map_flood_fill(t_map *map, char **map_copy, int x, int y);
int				map_color_texture_check(char *line);
int				map_metadata_add(t_map *map, char *line);
/* src/map/map_checks_2.c */
void			map_line_check(char *line);
int				map_color_check(char **colors);
/* src/map/map_color.c */
int				map_floor_color(t_map *map, char *line);
int				map_ceiling_color(t_map *map, char *line);
void			map_store_textures_and_colors(t_map *map, char *line);
int				map_plane_texture(t_map *map, char *line);
unsigned int	map_combine_rgb(unsigned int red, unsigned int green,
					unsigned int blue);
/* src/map/map_coordinates.c */
void			map_xy_coordinates(t_map *map, char *path);
int				map_no_coordinate(t_map *map, char *line);
int				map_so_coordinate(t_map *map, char *line);
int				map_we_coordinate(t_map *map, char *line);
int				map_ea_coordinate(t_map *map, char *line);
/* src/map/map_coordinates_2.c */
int				map_texture(t_map *map, char *line);
int				map_intro(t_map *map, char *line);
int				map_next_lvl(t_map *map, char *line);
void			map_find_direction(t_map *map, char *line, int *flag, int y);
void			map_process_row(t_map *map, char *line, int *y);
/* src/map/map_error_handling.c */
void			map_free_double_array(char **map);
/* src/map/map_ft_atof.c */
double			map_ft_atof(const char *str);
double			map_ft_atof_fractional_part(const char **str);
double			map_ft_atof_integer_part(const char **str);
int				map_ft_atof_parse_sign(const char **str);
const char		*map_ft_atof_skip_whitespace(const char *str);
/* src/map/map_plane_parsing.c */
int				map_find_available_object_slot(t_map *map);
void			map_parse_plane_details(t_map *map, int j, char **coordinates);
void			map_parse_normal_vector(t_map *map, int j,
					char **coordinates, int *i);
void			map_parse_plane_w_and_h(t_map *map,
					int j, char **coordinates, int *i);
void			map_parse_plane_coordinates(t_map *map,
					int j, char **coordinates, int *i);
/* src/map/map_utils.c */
void			map_init_values(t_map *map);
void			map_print(t_map *map);
void			map_direction_validation(char *line, int flag);
int				map_open_file(char *path);
/* src/map/map_utils_2.c */
void			map_deinit(t_map *map);
void			map_deinit_doublepointer(char **dstr);
/* src/img/img.c */
void			img_init(t_img *img, void *mlx, int w, int h);
bool			img_load(t_img *img, void *mlx, char *path);
void			img_deinit(t_img *img, void *mlx);
/* src/img/img_draw.c */
void			img_draw_rect(t_img *img, t_ipt tl, t_ipt br, t_color col);
void			img_clear(t_img *img, t_color col);
void			img_draw_line(t_img *img, t_ipt p1, t_ipt p2, t_color col);
/* src/img/img_fade.c */
void			img_green_fade(t_img *img);
/* src/img/img_put.c */
void			img_put_img_section_stencil(t_img *dst, t_imgsec *src,
					t_ipt dstpos, t_color col);
void			img_put_img(t_img *dst, t_img *src, int putx, int puty);
void			img_put_img_mid(t_img *dst, t_img *src, int putx, int puty);
/* src/img/img_pxl.c */
unsigned char	*img_getloc(t_img *img, int x, int y);
bool			img_inrange(t_img *img, int x, int y);
t_color			img_getpxl(t_img *img, int x, int y);
t_color			img_getpxlr(t_img *img, float x, float y);
void			img_putpxl(t_img *img, int x, int y, t_color c);
/* src/img/img_text.c */
void			img_put_char(t_img *img, t_img *font, t_cpt dst, char ch);
void			img_put_text(t_img *img, t_img *font, t_ipt dst, char *t);
void			img_put_text_extra(t_img *img,
					t_img *font, t_ipt dst, t_textinfo *t);
void			img_put_text_center(t_img *img,
					t_img *font, t_ipt dst, char *text);
/* src/vector/init.c */
t_vec3			vec3(float x, float y, float z);
t_vec3			vec3_from_vec(t_vec *v);
t_ipt			ipt(int x, int y);
t_cpt			cpt(t_color c, int x, int y);
t_rect			rect(int x1, int y1, int x2, int y2);
/* src/vector/vector.c */
t_vec			vec(float x, float y);
void			vec_print(t_pt *p);
t_vec			vec_from_vec3(t_vec3 *v);
/* src/vector/vector_ops_basic.c */
t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_sub(t_vec a, t_vec b);
t_vec			vec_scale(t_vec a, float f);
float			vec_len(t_vec v);
/* src/vector/vector_ops_extra.c */
t_vec			vec_normalize(t_vec v);
t_vec			vec_rotate(t_vec v, float r);
int				vec_direction(t_vec *v);
bool			vec_nonzero(t_vec *v);
float			vec_mul(t_vec v, t_vec w);
/* src/utils/utils.c */
int				ft_ternary_int(bool condition, int true_val, int false_val);
float			ft_ternary_float(bool cond, float true_val, float false_val);
int				map_safe_ft_atoi(char *color);
int				timediff(struct timeval *t1, struct timeval *t2);
bool			ft_endswith(const char *s, const char *needle);
void			*ft_xmalloc(size_t mem);
t_hitrec		hitnone(void);
/* src/utils/utils_direction.c */
float			angle_normalize(float angle);
int				angle_direction(float angle);
float			rot_fromchar(char o);
char			*str_direction(int d);
/* src/utils/utils_bits.c */
void			set_bit(unsigned char *c, unsigned int i, int val);
bool			get_bit(unsigned char c, unsigned int i);
/* src/utils/utils_file.c */
int				ft_filelen(char *path);
char			*ft_fileload(char *path, int *datalen);
/* src/utils/utils_float.c */
float			fclamp(float val, float min, float max);
int				fbetw(float val, float min, float max);
/* src/utils/utils_rect.c */
bool			rect_inside(t_rect *rect, t_pt pt);

#endif
