/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:26:00 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 20:19:00 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void			*img_path;
	void			*img_hero;
	void			*img_wall;
	void			*img_item;
	void			*img_exit;
	void			*img_door;
	void			*path1;
	void			*hero1;
	void			*wall1;
	void			*item1;
	void			*exit1;
	void			*door1;
	void			*path2;
	void			*hero2;
	void			*wall2;
	void			*item2;
	void			*exit2;
	void			*door2;
	void			*wins;
	int				win_x;
	int				win_y;
	char			**map;
	char			folder;
	int				x_pos;
	int				y_pos;
	int				valid[3];
	int				items_found;
	int				exit_found;
	int				items_left;
	int				steps_taken;
	void			*mlx;
	void			*win;
	int				its_over;
	int				aframe;
	int				iframe;
}					t_data;

# define XK_ESCAPE	0xff1b
# define XK_W		0x0077
# define XK_S		0x0073
# define XK_A		0x0061
# define XK_D		0x0064

int		builddata(t_data *data, void *mlx);
void	buildmap(t_data *data, int fd);
char	*get_next_line(int fd);
void	*sub_calloc(size_t count, size_t size);
void	display(t_data *data);
void	display_funky(int i, int j, t_data *data);
void	display_party(int i, int j, t_data *data);
int		valid_map(t_data *data);
int		valid_path(int x, int y, t_data *data);
int		key_hook(int keycode, t_data *data);
void	move(int x, int y, t_data *data);
void	map_size(t_data *data);
int		getrekt(t_data *data, int crash);
int		realmap(t_data *data);
int		mapman(int argc, char **argv);
int		path_funky(int x, int y, t_data *data);
int		anime(t_data *data);
void	sprite(t_data *data, int set);
void	the_goods(t_data *data, void *mlx);
void	destruction(t_data *data);

#endif
