/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:35:49 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 23:07:16 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_texture_x(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.play_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.play_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	get_pxl_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->addr + (y * img->linen + x * (img->bpp / 8));
	return (*(int *)dst);
}

int	blend_color(int bg, int fg, float a)
{
	int	b[3];
	int	f[3];
	int	i;

	if (a <= 0.0f)
		return (bg);
	if (a >= 1.0f)
		return (fg);
	b[0] = (bg >> 16) & 0xFF;
	b[1] = (bg >> 8) & 0xFF;
	b[2] = bg & 0xFF;
	f[0] = (fg >> 16) & 0xFF;
	f[1] = (fg >> 8) & 0xFF;
	f[2] = fg & 0xFF;
	i = 0;
	while (i < 3)
	{
		b[i] = (int)(b[i] * (1.0f - a) + f[i] * a);
		if (b[i] > 255)
			b[i] = 255;
		i = i + 1;
	}
	return ((b[0] << 16) | (b[1] << 8) | b[2]);
}

void	draw_wall_column_alpha(t_game *game, t_ray *ray, int x, double a)
{
	t_img	*tex;
	double	data[4];
	int		y;
	int		tex_y;

	if (a <= 0.0)
		return ;
	tex = ft_select_wall_texture(game, ray);
	if (!tex || !tex->img)
		return ;
	data[0] = get_texture_x(game, ray, tex);
	data[1] = 1.0 * tex->height / ray->line_height;
	data[2] = (ray->draw_start - game->win_h / 2
			+ ray->line_height / 2) * data[1];
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)data[2] & (tex->height - 1);
		data[3] = blend_color(get_pxl_color(&game->frame.img, x, y),
				*(int *)(tex->addr + (tex_y * tex->linen + (int)data[0]
						* (tex->bpp / 8))), a);
		my_mlx_pixel_put(&game->frame.img, x, y, (int)data[3]);
		data[2] = data[2] + data[1];
		y = y + 1;
	}
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		printf("ESC pressed - Exiting Game\n");
		ft_cleanup_game(game);
		exit(0);
	}
	else if (keycode == KEY_ENTER && (game->gmover.state == GAME_OVER
			|| game->gmover.state == GAME_WIN))
		return (ft_reset_game(game), 0);
	else if (keycode == KEY_W)
		game->input.keys |= FWRD;
	else if (keycode == KEY_S)
		game->input.keys |= BWRD;
	else if (keycode == KEY_A)
		game->input.keys |= LEFT;
	else if (keycode == KEY_D)
		game->input.keys |= RIGHT;
	else if (keycode == KEY_LEFT)
		game->input.keys |= TURN_L;
	else if (keycode == KEY_RIGHT)
		game->input.keys |= TURN_R;
	else if (keycode == KEY_SPACE)
		check_nearby_doors(game);
	return (0);
}
