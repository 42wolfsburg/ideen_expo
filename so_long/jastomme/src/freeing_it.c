/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:59:48 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 10:44:30 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_list(t_map *head)
{
	t_map	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->line);
		free(temp);
	}
}

static void	free_resources(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->img[i])
		{
			mlx_destroy_image(game->mlx, game->img[i]);
			game->img[i] = NULL;
		}
		i++;
	}
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		mlx_loop_end(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

static int	exit_program(t_game *game)
{
	if (game->map)
	{
		free_list(game->map);
		game->map = NULL;
	}
	exit(0);
}

int	exit_game(t_game *game, char *str)
{
	ft_printf("%s\n", str);
	free_resources(game);
	exit_program(game);
	return (0);
}

void	input_exit(t_game *game, char *str)
{
	ft_printf("%s", str);
	free_list(game->map);
	exit(0);
}
