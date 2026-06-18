/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:30:25 by loandrad          #+#    #+#             */
/*   Updated: 2023/06/08 15:55:52 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITERATIONS 60
# define EVENT_CLOSE_BTN 17
# ifdef LINUX
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_SPACE 32
#  define KEY_ONE 49
#  define KEY_TWO 50
#  define MOUSE_WHEEL_UP 4
#  define MOUSE_WHEEL_DOWN 5
# else
#  define KEY_ESC 53
#  define KEY_UP 125
#  define KEY_DOWN 126
#  define KEY_LEFT 124
#  define KEY_RIGHT 123
#  define KEY_SPACE 49
#  define KEY_ONE 18
#  define KEY_TWO 19
#  define MOUSE_WHEEL_UP 5
#  define MOUSE_WHEEL_DOWN 4
# endif
# define MANDELBROT 1
# define JULIA 2

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	kr;
	double	ki;
	int		*palette;
	int		color_count;
	int		color;
}	t_fractol;

int		mandelbrot(double cr, double ci);
int		julia(t_fractol *f, double zr, double zi);
void	render(t_fractol *f);
void	toggle_color(t_fractol *f);
int		key_event(int keycode, t_fractol *mlx);
int		mouse_event(int keycode, int x, int y, t_fractol *mlx);
void	clean_init(t_fractol *f);
void	reinit_img(t_fractol *f);
void	init(t_fractol *f);
void	layout(t_fractol *f);
double	ft_atof(char *str);
int		quit(t_fractol *mlx);
void	clean_up(int error_code, t_fractol *f);
void	help_msg(t_fractol *f);
int		error(char *str1, int errno);
int		ft_strlen(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		find_char(char *str, char a);

#endif
