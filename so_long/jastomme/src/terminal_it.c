/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_it.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:00:22 by jastomme          #+#    #+#             */
/*   Updated: 2026/05/13 10:40:26 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*g_game = NULL;

void	signal_handler(int sig)
{
	(void)sig;
	if (g_game)
		game_over(g_game);
}

void	game_over(t_game *game)
{
	ft_printf("GAME OVER!\n");
	exit_game(game, "");
}

void	you_won(t_game *game)
{
	ft_printf("YOU WON!\n");
	exit_game(game, "");
}

void	no_exit(void)
{
	ft_printf("COLLECT THEM ALL FIRST!\n");
}

void	render_steps(t_game *game)
{
	char	*step_str;

	step_str = ft_itoa(game->steps);
	mlx_string_put(game->mlx, game->win, 10, 50, 0xFF000F, "Steps taken: ");
	mlx_string_put(game->mlx, game->win, 100, 50, 0xFF00, step_str);
	free(step_str);
}
