/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:22:14 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 20:06:51 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CVb3d2023
// rm $HOME/.config/BraveSoftware/Brave-Browser/SingletonLock

// TO DO:
// double check req.

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	int		fd;
	t_data	data;

	fd = mapman(argc, argv);
	mlx = mlx_init();
	data.mlx = mlx;
	builddata(&data, mlx);
	buildmap(&data, fd);
	map_size(&data);
	mlx_win = mlx_new_window(mlx, data.win_x * 100, data.win_y * 100,
			"The Bizzare Adventures of Choli");
	data.win = mlx_win;
	data.items_left = 0;
	display(&data);
	if (data.valid[0] != 1 || data.valid[1] != 1 || realmap(&data)
		|| valid_map(&data) || data.items_found != data.items_left
		|| data.exit_found == 0)
		return (getrekt(&data, 1));
	mlx_key_hook(mlx_win, key_hook, &data);
	mlx_hook(mlx_win, 17, 0, getrekt, &data);
	mlx_loop_hook(mlx, anime, &data);
	mlx_loop(mlx);
	return (0);
}

int	builddata(t_data *data, void *mlx)
{
	int		s;
	int		f;
	int		fd;

	fd = open("./maps/test_map.ber", O_RDONLY);
	s = 100;
	f = 300;
	data->aframe = 0;
	data->steps_taken = 0;
	data->path1 = mlx_xpm_file_to_image(mlx, "./sprites/path1.xpm", &s, &s);
	data->hero1 = mlx_xpm_file_to_image(mlx, "./sprites/hero1.xpm", &s, &s);
	data->wall1 = mlx_xpm_file_to_image(mlx, "./sprites/wall1.xpm", &s, &s);
	data->item1 = mlx_xpm_file_to_image(mlx, "./sprites/item1.xpm", &s, &s);
	data->exit1 = mlx_xpm_file_to_image(mlx, "./sprites/exit1.xpm", &s, &s);
	data->door1 = mlx_xpm_file_to_image(mlx, "./sprites/door1.xpm", &s, &s);
	data->wins = mlx_xpm_file_to_image(mlx, "./sprites/wins.xpm", &f, &s);
	data->img_path = data->path1;
	data->img_hero = data->hero1;
	data->img_wall = data->wall1;
	data->img_item = data->item1;
	data->img_exit = data->exit1;
	data->img_door = data->door1;
	data->map = sub_calloc(10240, sizeof(char **));
	return (0);
	buildmap(data, fd);
}

void	buildmap(t_data *data, int fd)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	data->path2 = NULL;
	data->iframe = 0;
	data->its_over = 0;
	while (j)
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i] == NULL)
			j = 0;
		i++;
	}
	data->win_y = i - 1;
}

void	display(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i != 3)
		data->valid[i] = 0;
	i = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			display_funky(i, j, data);
			i++;
		}
		i = 0;
		j++;
	}
}

int	realmap(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			if (data->map[j][i] != '1' && data->map[j][i] != '0'
			&& data->map[j][i] != 'E' && data->map[j][i] != 'P'
			&& data->map[j][i] != 'C' && data->map[j][i] != '\n')
			{
				ft_printf("Ooops!\n");
				return (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
