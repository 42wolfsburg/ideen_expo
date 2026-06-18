/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:27:20 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 22:35:01 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_img	*ft_select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->tex.tex[WALL_E]);
		return (&game->tex.tex[WALL_W]);
	}
	if (ray->ray_dir_y > 0)
		return (&game->tex.tex[WALL_S]);
	return (&game->tex.tex[WALL_N]);
}

int	is_collected(t_game *game, int map_x, int map_y)
{
	int	i;

	i = 0;
	while (i < game->colls.total)
	{
		if ((int)game->colls.list[i].col_x == map_x
			&& (int)game->colls.list[i].col_y == map_y
			&& game->colls.list[i].collected)
			return (1);
		i++;
	}
	return (0);
}

void	update_collectible_frames(t_game *game)
{
	static int	frame_counter = 0;
	int			idx;

	frame_counter = frame_counter + 1;
	if (frame_counter < game->coll_anim_frames)
		return ;
	frame_counter = 0;
	idx = 0;
	while (idx < game->colls.total)
	{
		if (game->colls.list[idx].collected == 0)
		{
			game->colls.list[idx].current_frame
				= (game->colls.list[idx].current_frame + 1) % COLL_FRAME;
		}
		idx = idx + 1;
	}
}

void	update_enemy_animation(t_game *game)
{
	static int	frame_counter = 0;
	int			idx;

	frame_counter = frame_counter + 1;
	if (frame_counter < game->enemy_anim_frames)
		return ;
	frame_counter = 0;
	idx = 0;
	while (idx < game->enemies.ene_count)
	{
		if (game->enemies.list[idx].alive != 0)
		{
			game->enemies.list[idx].current_frame
				= (game->enemies.list[idx].current_frame + 1) % ENE_FRAME;
		}
		idx = idx + 1;
	}
}

void	update_enemy_positions(t_game *game)
{
	double	dx;
	double	dy;
	double	dist;
	int		idx;

	idx = 0;
	while (idx < game->enemies.ene_count)
	{
		if (game->enemies.list[idx].alive != 0)
		{
			dx = game->player.play_x - game->enemies.list[idx].ene_x;
			dy = game->player.play_y - game->enemies.list[idx].ene_y;
			dist = sqrt(dx * dx + dy * dy);
			if (dist > 0.5)
			{
				game->enemies.list[idx].ene_x = game->enemies.list[idx].ene_x
					+ (dx / dist) * game->enemies.list[idx].ene_speed;
				game->enemies.list[idx].ene_y = game->enemies.list[idx].ene_y
					+ (dy / dist) * game->enemies.list[idx].ene_speed;
			}
		}
		idx = idx + 1;
	}
}
