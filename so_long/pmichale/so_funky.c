/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_funky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:38:38 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 20:19:26 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	getrekt(t_data *data, int crash)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	destruction(data);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	if (crash == 1)
		ft_printf("Error, Map Error\n");
	exit(1);
	return (1);
}

int	mapman(int argc, char **argv)
{
	int	len;
	int	fd;

	len = 0;
	if (argc != 2)
	{
		ft_printf("Error, No/Too many Argument/s\n");
		exit(1);
	}
	while (argv[1][len])
		len++;
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'b'
	|| argv[1][len - 2] != 'e' || argv[1][len - 1] != 'r')
	{
		ft_printf("Error, not a .ber\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error, File not found\n");
		exit(1);
	}
	return (fd);
}

void	display_funky(int i, int j, t_data *data)
{
	void	*ml;
	void	*mw;

	ml = data->mlx;
	mw = data->win;
	if (data->map[j][i] == '1')
		mlx_put_image_to_window(ml, mw, data->img_wall, i * 100, j * 100);
	if (data->map[j][i] == '0' || data->map[j][i] == 'O')
		mlx_put_image_to_window(ml, mw, data->img_path, i * 100, j * 100);
	if (data->map[j][i] == 'P' || data->map[j][i] == 'p')
	{
		data->x_pos = i;
		data->y_pos = j;
		data->valid[0]++;
		mlx_put_image_to_window(ml, mw, data->img_hero, i * 100, j * 100);
	}
	display_party(i, j, data);
}

int	path_funky(int x, int y, t_data *data)
{
	if (data->map[y][x] == 'O')
		return (0);
	if (data->map[y][x] == 'c')
		return (0);
	if (data->map[y][x] == '1')
		return (0);
	if (data->map[y][x] == 'p')
		return (0);
	if (data->map[y][x] == 'P')
		data->map[y][x] = 'p';
	if (data->map[y][x] == 'E')
	{
		data->exit_found++;
		return (0);
	}
	if (data->map[y][x] == '0')
		data->map[y][x] = 'O';
	if (data->map[y][x] == 'C')
	{
		data->map[y][x] = 'c';
		data->items_found++;
	}
	return (1);
}

void	display_party(int i, int j, t_data *data)
{
	void	*ml;
	void	*mw;

	ml = data->mlx;
	mw = data->win;
	if (data->map[j][i] == 'E' || data->map[j][i] == 'e')
	{
		data->map[j][i] = 'E';
		if (data->items_left == 0)
			mlx_put_image_to_window(ml, mw, data->img_exit, i * 100, j * 100);
		else
			mlx_put_image_to_window(ml, mw, data->img_door, i * 100, j * 100);
		data->valid[1]++;
	}
	if (data->map[j][i] == 'C')
	{
		mlx_put_image_to_window(ml, mw, data->img_item, i * 100, j * 100);
		data->valid[2]++;
		data->items_left++;
	}
	if (data->map[j][i] == 'c')
		mlx_put_image_to_window(ml, mw, data->img_item, i * 100, j * 100);
	if (data->its_over == 1)
		mlx_put_image_to_window(ml, mw, data->wins, (data->win_x * 100)
			/ 2 - 150, (data->win_y * 100) / 2 -50);
}
