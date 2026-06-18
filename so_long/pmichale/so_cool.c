/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_cool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:38:35 by pmichale          #+#    #+#             */
/*   Updated: 2024/02/09 19:09:20 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_map(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = -1;
	while (data->map[0][++i])
		if (data->map[0][i] != '1' && data->map[0][i] != '\n')
			return (1);
	len = i - 2;
	i = -1;
	while (data->map[++j + 1])
		if (data->map[j][0] != '1' || data->map[j][len] != '1'
		|| data->map[j][len + 1] != '\n')
			return (1);
	while (data->map[j][++i])
		if (data->map[j][i] != '1' || i > len)
			return (1);
	data->items_found = 0;
	data->exit_found = 0;
	valid_path(data->x_pos, data->y_pos, data);
	return (0);
}

int	valid_path(int x, int y, t_data *data)
{
	if (!path_funky(x, y, data))
		return (0);
	if (valid_path(x - 1, y, data))
		return (1);
	if (valid_path(x + 1, y, data))
		return (1);
	if (valid_path(x, y - 1, data))
		return (1);
	if (valid_path(x, y + 1, data))
		return (1);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	(void) data;
	if (keycode == XK_ESCAPE)
		getrekt(data, 0);
	if (keycode == XK_S)
	{
		move(0, 1, data);
		display(data);
	}
	if (keycode == XK_W)
	{
		move(0, -1, data);
		display(data);
	}
	if (keycode == XK_A)
	{
		move(-1, 0, data);
		display(data);
	}
	if (keycode == XK_D)
	{
		move(1, 0, data);
		display(data);
	}
	ft_printf("big steppies taken:%i\n", data->steps_taken);
	return (0);
}

void	move(int x, int y, t_data *data)
{
	if (data->its_over == 1)
		return ;
	if (data->map[data->y_pos + y][data->x_pos + x] == 'O')
	{
		data->map[data->y_pos][data->x_pos] = 'O';
		data->map[data->y_pos + y][data->x_pos + x] = 'p';
		data->steps_taken++;
	}
	if (data->map[data->y_pos + y][data->x_pos + x] == 'c')
	{
		data->map[data->y_pos][data->x_pos] = 'O';
		data->map[data->y_pos + y][data->x_pos + x] = 'p';
		data->items_left--;
		data->steps_taken++;
	}
	if (data->map[data->y_pos + y][data->x_pos + x] == 'E')
	{
		if (data->items_left != 0)
			return ;
		data->map[data->y_pos][data->x_pos] = 'O';
		data->map[data->y_pos + y][data->x_pos + x] = 'E';
		data->steps_taken++;
		data->its_over = 1;
		ft_printf("And thus Choli completed her epic Adventure. You win!\n");
	}
}

void	map_size(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[0][i] != '\n')
		i++;
	data->win_x = i;
}
