/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:27:10 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/26 16:27:34 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
// # include "../../../minilibx-linux/mlx.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
/* ========================================
   DEFINES
   ======================================== */

// Window settings
# define MAX_LINES 1024
# define WIN_WIDTH 3480
# define WIN_HEIGHT 2160
# define WIN_TITLE "Cub3D"

# define FOV_P 0.66
# define FOV_N -0.66

// Key codes (Linux)
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_T 116
# define KEY_L 108

// Event codes
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_DESTROY 17

/* ========================================
   STRUCTURES
   ======================================== */

// Image buffer for fast rendering
typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

// Texture paths
typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor_tex;
	char		*ceiling_tex;
	t_img		north_img;
	t_img		south_img;
	t_img		west_img;
	t_img		east_img;
	t_img		floor_img;
	t_img		ceiling_img;
}				t_textures;

// RGB color
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

// Player data
typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

// Map data
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char		*first_line;
}				t_map;

typedef struct s_timing
{
	double		last_frame_time;
	double		fps_timer;
	int			frame_count;
	double		fps;
}				t_timing;

// Main game structure
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	int			use_floor_texture;
	int			use_ceiling_texture;
	int			texture_mode;
	int			torch_mode;
	t_map		map;
	t_player	player;
	t_timing	timing;
	int			needs_redraw;
}				t_data;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ========================================
   FUNCTION PROTOTYPES
   ======================================== */

// Window management (window.c)
int				init_window(t_data *data);
void			destroy_window(t_data *data);

// Event handlers (events.c)
int				handle_escape(int keycode, t_data *data);
int				handle_movement_keys(int keycode, t_data *data);
int				handle_rotation_keys(int keycode, t_data *data);
int				handle_keypress(int keycode, t_data *data);
int				handle_close(t_data *data);
void			setup_hooks(t_data *data);

// Core utilities (utils.c)
void			print_controls(void);
void			error_exit(char *message);

// Debug utilities (debug.c)
void			draw_background(t_data *data);
void			draw_minimap(t_data *data);
void			debug_print_config(t_data *data);
void			debug_print_colors(t_color *floor, t_color *ceiling);
void			debug_print_textures(t_textures *tex);

void			print_column_numbers(int width);
void			print_horizontal_border(int width);
void			print_map_row(int y, t_map *map);
void			debug_print_map_detailed(t_map *map);

double			get_time(void);
void			cleanup_and_exit(t_data *data);
int				handle_arguments(int argc, char **argv);
#endif
