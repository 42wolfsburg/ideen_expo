/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:46:12 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:47:35 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	get_sprite_tex_x(t_sprite_cast *cast, int stripe, int tex_width)
{
	int	tex_x;

	tex_x = (int)(256 * (stripe - (-cast->sprite_width / 2
					+ cast->sprite_screen_x)) * tex_width
			/ cast->sprite_width) / 256;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	return (tex_x);
}

void	draw_sprite_vertical(t_game *game, int data[4], t_img *tex,
			t_sprite_cast *cast)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;

	y = cast->draw_start_y;
	while (y < cast->draw_end_y)
	{
		d = (y - game->win_h / 2 + cast->sprite_height / 2) * 256;
		tex_y = ((d * tex->height) / cast->sprite_height) / 256;
		color = *(int *)(tex->addr + (tex_y * tex->linen + data[0]
					* (tex->bpp / 8)));
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&game->frame.img, data[1], y, color);
		y = y + 1;
	}
}

void	draw_sprite_stripes(t_game *g, t_sprite *s,	t_sprite_cast *c, double ty)
{
	t_img	*tex;
	int		stripe;
	int		data[2];

	if (!g->sprites.zbuffer)
		return ;
	tex = &g->tex.tex[s->tex_id];
	stripe = c->draw_start_x;
	if (stripe < 0)
		stripe = 0;
	while (stripe < c->draw_end_x && stripe < g->win_w)
	{
		if (ty > 0 && ty < g->sprites.zbuffer[stripe])
		{
			data[0] = get_sprite_tex_x(c, stripe, tex->width);
			data[1] = stripe;
			draw_sprite_vertical(g, data, tex, c);
		}
		stripe++;
	}
}

void	calculate_sprite_cast(t_game *game, t_sprite_cast *cast, double tx,
	double ty)
{
	cast->transform_x = tx;
	cast->transform_y = ty;
	cast->sprite_screen_x = (int)((game->win_w / 2) * (1 + tx / ty));
	cast->sprite_height = abs((int)(game->win_h / ty));
	cast->sprite_width = cast->sprite_height;
	cast->draw_start_y = -cast->sprite_height / 2 + game->win_h / 2;
	if (cast->draw_start_y < 0)
		cast->draw_start_y = 0;
	cast->draw_end_y = cast->sprite_height / 2 + game->win_h / 2;
	if (cast->draw_end_y >= game->win_h)
		cast->draw_end_y = game->win_h - 1;
	cast->draw_start_x = -cast->sprite_width / 2 + cast->sprite_screen_x;
	if (cast->draw_start_x < 0)
		cast->draw_start_x = 0;
	cast->draw_end_x = cast->sprite_width / 2 + cast->sprite_screen_x;
	if (cast->draw_end_x >= game->win_w)
		cast->draw_end_x = game->win_w - 1;
}

void	draw_sprite_column(t_game *game, t_sprite *sprite,
			double tx, double ty)
{
	t_sprite_cast	cast;

	calculate_sprite_cast(game, &cast, tx, ty);
	draw_sprite_stripes(game, sprite, &cast, ty);
}
