/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:45:43 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 22:45:54 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_cleanup_lists(t_game *game)
{
	if (game->doors.list)
		free(game->doors.list);
	if (game->colls.list)
		free(game->colls.list);
	if (game->enemies.list)
		free(game->enemies.list);
	if (game->sprites.list)
		free(game->sprites.list);
	if (game->sprites.zbuffer)
		free(game->sprites.zbuffer);
}

void	ft_cleanup_textures(t_game *game)
{
	int	index;

	index = 0;
	while (index < COUNT)
	{
		if (game->tex.tex[index].img)
			mlx_destroy_image(game->mlx, game->tex.tex[index].img);
		index++;
	}
}

void	ft_cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
		ft_cleanup_textures(game);
	ft_cleanup_lists(game);
	if (game->frame.img.img && game->mlx)
		mlx_destroy_image(game->mlx, game->frame.img.img);
	if (game->map.raw_map)
	{
		free_strings(game->map.raw_map);
		game->map.raw_map = NULL;
	}
	if (game->map.map)
	{
		free_strings(game->map.map);
		game->map.map = NULL;
	}
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
