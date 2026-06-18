/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_anime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:36:07 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 20:18:45 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	anime(t_data *data)
{
	usleep(5000);
	data->iframe++;
	if (data->iframe != 100)
		return (0);
	data->iframe = 0;
	if (data->path2 == NULL)
		the_goods(data, data->mlx);
	if (data->aframe == 0)
	{
		sprite(data, data->aframe);
		data->aframe = 1;
		display(data);
	}
	else if (data->aframe == 1)
	{
		sprite(data, data->aframe);
		data->aframe = 0;
		display(data);
	}
	return (0);
}

void	sprite(t_data *data, int set)
{
	if (set == 0)
	{
		data->img_path = data->path2;
		data->img_hero = data->hero2;
		data->img_wall = data->wall2;
		data->img_item = data->item2;
		data->img_exit = data->exit2;
		data->img_door = data->door2;
	}
	if (set == 1)
	{
		data->img_path = data->path1;
		data->img_hero = data->hero1;
		data->img_wall = data->wall1;
		data->img_item = data->item1;
		data->img_exit = data->exit1;
		data->img_door = data->door1;
	}
}

void	the_goods(t_data *data, void *mlx)
{
	int	s;

	s = 100;
	data->path2 = mlx_xpm_file_to_image(mlx, "./sprites/path2.xpm", &s, &s);
	data->hero2 = mlx_xpm_file_to_image(mlx, "./sprites/hero2.xpm", &s, &s);
	data->wall2 = mlx_xpm_file_to_image(mlx, "./sprites/wall2.xpm", &s, &s);
	data->item2 = mlx_xpm_file_to_image(mlx, "./sprites/item2.xpm", &s, &s);
	data->exit2 = mlx_xpm_file_to_image(mlx, "./sprites/exit2.xpm", &s, &s);
	data->door2 = mlx_xpm_file_to_image(mlx, "./sprites/door2.xpm", &s, &s);
}

void	destruction(t_data *data)
{
	mlx_destroy_image(data->mlx, data->path1);
	mlx_destroy_image(data->mlx, data->hero1);
	mlx_destroy_image(data->mlx, data->wall1);
	mlx_destroy_image(data->mlx, data->item1);
	mlx_destroy_image(data->mlx, data->exit1);
	mlx_destroy_image(data->mlx, data->door1);
	mlx_destroy_image(data->mlx, data->path2);
	mlx_destroy_image(data->mlx, data->hero2);
	mlx_destroy_image(data->mlx, data->wall2);
	mlx_destroy_image(data->mlx, data->item2);
	mlx_destroy_image(data->mlx, data->exit2);
	mlx_destroy_image(data->mlx, data->door2);
	mlx_destroy_image(data->mlx, data->wins);
}
