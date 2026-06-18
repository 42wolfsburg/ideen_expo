/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:35:59 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 13:51:30 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <stdbool.h>
# include <libft.h>
# include "keys.h"
# include "load_fdf.h"

# define C_WHITE		0x00ffffff
# define C_RED			0x00ff0000
# define C_GREEN		0x0000ff00
# define C_BLUE			0x000000ff
# define C_ORANGE		0xaacc8800
# define C_FDF			0x00ffffff
# define C_MODEL		C_ORANGE

typedef float	t_mat4[4][4];
typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_vertex
{
	float	x;
	float	y;
	float	z;
	t_color	col;
}	t_cvec;

// 2d point using int
typedef struct s_point
{
	int		x;
	int		y;
}	t_point;

// 2d point using int - includes color
typedef struct s_cpoint
{
	int			x;
	int			y;
	t_color		col;
}	t_cpoint;

// 2d point using float
typedef struct s_fpoint
{
	float		x;
	float		y;
}	t_fpoint;

// edge, from index a to index b
typedef struct s_edge
{
	int		a;
	int		b;
}	t_edge;

// model
typedef struct s_model
{
	char	*name;
	size_t	nverts;
	size_t	nedges;
	t_cvec	*verts;
	t_edge	*edges;
}	t_model;

typedef struct s_image
{
	void	*img;
	void	*data;
	int		width;
	int		height;
	int		bpp;
	int		linelen;
	int		endian;
}	t_image;

typedef struct s_disp
{
	void		*mlx;
	void		*win;
	t_list		*models;
	t_image		buffer;
	int			mod_active;
	t_point		center_old;
	t_point		center;
	float		yaw;
	float		roll;
	bool		shift;
	bool		showaxes;
	bool		autorot;
	bool		mouserot;
	bool		update;
	t_mat4		mat;
	int			width;
	int			height;
	int			mousex;
	int			mousey;
	float		z_size;
	float		zoom;
	bool		pan;
	t_point		dragstart;
	long		ticks;
}	t_disp;

// state for Bresenham algo (only to save vars)
struct s_linestate
{
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			error;
	int			e2;
	int			steps;
	int			i;
	bool		interpol;
	t_color		col;
};

/* $$proto_start$$ */

/* color.c */
unsigned char	cl_trans(t_color c);
unsigned char	cl_opac(t_color c);
unsigned char	cl_red(t_color c);
unsigned char	cl_green(t_color c);
unsigned char	cl_blue(t_color c);
t_color			clt(unsigned char r, unsigned char g, \
			unsigned char b, unsigned char t);
t_color			cl(unsigned char r, unsigned char g, unsigned char b);
t_color			cl_combine(t_color c1, t_color c2);
t_color			clt_to_cl(t_color c);
t_color			cl_add(t_color c1, t_color c2);
t_color			cl_interpol(t_color from, t_color to, int i, int max);
/* disp.c */
bool			disp_init(t_disp *disp, int w, int h, char *title);
void			disp_reset(t_disp *disp);
void			disp_hook(t_disp *disp);
long			mtime(void);
bool			disp_load(t_disp *disp, int nobj, char **files);
void			disp_destroy(t_disp *disp);
t_model			*disp_getmodel(t_disp *disp);
t_fpoint		project_iso(t_cvec v);
t_fpoint		disp_project(t_disp *disp, t_vec v);
t_vec			disp_project_cvv(t_disp *disp, t_vec v);
void			disp_draw3dline(t_disp *disp, t_cvec v, t_cvec w);
void			disp_draw_axes(t_disp *disp);
void			disp_draw_model(t_disp *disp);
void			disp_frame_init(t_disp *disp);
void			disp_frame_init_rot(t_disp *disp);
void			disp_draw(t_disp *disp);
int				disp_loop(t_disp *disp);
/* input.c */
void			keys_handle_view(t_disp *disp, int key);
void			keys_handle_rot(t_disp *disp, int key);
void			mouse_handle_zoom(t_disp *disp, int button);
/* events.c */
int				event_key(int key, void *arg);
int				event_keydown(int key, void *arg);
int				event_keyup(int key, void *arg);
int				event_mouse(int button, int x, int y, void *param);
int				event_buttonpress(int button, int x, int y, void *param);
int				event_buttonrelease(int button, int x, int y, void *param);
int				event_expose(void *arg);
int				event_test(int key, void *arg);
int				event_destroy(void *arg);
/* fdf.c */
int				fdf_linelen(char *s);
void			fdf_line_del(void *arg);
void			fdf_getsize(t_fdf fdf, int *x, int *y);
void			fdf_print_node(void *node);
void			fdf_print_line(void *arg);
/* image.c */
t_image			img_new(void *mlx, int width, int height);
bool			img_putpxl(t_image *img, int x, int y, unsigned int value);
void			img_line(t_image *img, t_cpoint p1, t_cpoint p2);
/* load_model.c */
t_model			*model_load(const char *file);
void			model_from_fdf_make_edges(t_model *mod, int sizex, int sizey);
void			model_from_fdf_make_verts( \
			t_model *mod, t_fdf fdf, int sizex, int sizey);
t_model			*model_from_fdf(t_fdf *fdf);
void			model_normalize(t_model *mod);
/* matrix.c */
t_vec4			vecmul(t_mat4 mat, t_vec4 v);
void			mat4_copy(t_mat4 to, t_mat4 from);
void			matmul(t_mat4 mat1, t_mat4 mat2);
void			mat_rotation_int(t_mat4 m, float a, float b, float c);
void			mat_rotation(t_mat4 m, float a, float b, float c);
void			mat_identity(t_mat4 m);
/* model.c */
t_model			*model_new(size_t nverts, size_t nedges);
void			model_del(void *arg);
void			*model_del_null(void *arg);
/* vector.c */
t_vec			vec(float x, float y, float z);
t_vec4			vec_from_vec4(t_vec v);
t_vec			vec_normalize(t_vec4 v);
t_vec			vec_from_cvec(t_cvec v);
void			cvec_setminmax(t_cvec *v, t_vec *min, t_vec *max);
void			cvec_print(t_cvec v);
void			vec_print(t_vec v);
void			vec4_print(t_vec4 v);
/* vertex.c */
t_point			pt(int x, int y);
t_cpoint		cpt(int x, int y, t_color col);
t_fpoint		fpt(float x, float y);
t_fpoint		fpt_from_vec(t_vec v);
t_cvec			cvec_translate(t_cvec v, t_cvec w);
t_cvec			cvec(float x, float y, float z, t_color cl);
float			to_degrees(float val);
float			from_degrees(float val);
t_cvec			v_inv(t_cvec v);
t_edge			edge(int a, int b);
/* point_ops.c */
void			fpt_scale(t_fpoint *p, float f);
void			fpt_translate(t_fpoint *p, t_fpoint q);

/* $$proto_end$$ */

/* utils.c */
// float			from_deg(float deg);
// float			to_deg(float rad);

void			xmlx_destroy(void *mlx);

# ifdef LINUX

void			xmlx_mouse_get_pos(void *mlx, void *win, int *x, int *y);

# else

void			xmlx_mouse_get_pos(void *mlx, void *win, int *x, int *y);

# endif

#endif