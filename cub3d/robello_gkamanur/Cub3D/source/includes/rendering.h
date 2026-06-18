/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:27:19 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/26 13:38:18 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05

typedef struct s_minimap
{
	int		scale;
	int		offset_x;
	int		offset_y;
}			t_minimap;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
}			t_ray;

// minimap
void		draw_minimap_cell(t_data *data, int map_x, int map_y,
				t_minimap *mm);
void		draw_minimap_grid(t_data *data, t_minimap *mm);
int			get_minimap_color(t_data *data, int map_x, int map_y);
void		draw_player_dot(t_data *data, t_minimap *mm);
void		draw_player_direction(t_data *data, t_minimap *mm);
void		draw_minimap(t_data *data);

// movement
int			is_valid_position(t_data *data, double x, double y);
void		rotate_right(t_data *data);
void		rotate_left(t_data *data);
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		strafe_left(t_data *data);
void		strafe_right(t_data *data);

// performance
void		update_fps(t_data *data);
void		limit_framerate(t_data *data, int target_fps);
int			get_raycast_step(void);
void		duplicate_column(t_data *data, int src_x, int count);
void		fill_pixels_batch(int *pixels, int start, int end, int color);
void		fast_background_fill(t_data *data, int ceiling_color,
				int floor_color);
int			should_use_low_quality(double distance);

// raycast
void		calc_wall_params(t_data *data, t_ray *ray);
t_img		*select_wall_texture(t_data *data, t_ray *ray);
int			calc_texture_x(t_ray *ray, t_img *texture);
void		init_ray_params(t_data *data, int x, t_ray *ray);
void		init_ray_params_y(t_data *data, t_ray *ray);
int			check_wall_hit(t_data *data, t_ray *ray);
void		perform_dda(t_data *data, t_ray *ray);
void		draw_wall_column(t_data *data, t_ray *ray, t_img *tex, int x);
void		cast_ray(t_data *data, int x);
void		dup_col_raycast(t_data *data, int x, int step);
void		raycast(t_data *data);

// render
int			load_texture(t_data *data, t_img *tex, char *path);
int			load_wall_textures(t_data *data);
int			load_floor_ceiling_textures(t_data *data);
int			load_textures(t_data *data);

void		put_pixel_to_img(t_img *img, int x, int y, int color);
int			get_texture_pixel(t_img *texture, int x, int y);
void		fill_pixels_unrolled(int *pixels, int start, int end, int color);

void		render_background_color(t_data *data);
void		render_background_texture(t_data *data);
void		render_background(t_data *data);

void		render_ceiling_textured(t_data *data);
void		render_ceiling_color(t_data *data, int color);
void		render_ceiling(t_data *data);

void		render_floor_textured(t_data *data);
void		render_floor_color(t_data *data, int color);
void		render_floor(t_data *data);

int			init_image(t_data *data);
void		render_frame(t_data *data);

void		request_redraw(t_data *data);
int			needs_redraw(t_data *data);
void		clear_redraw_flag(t_data *data);
int			smooth_render_loop(t_data *data);
#endif