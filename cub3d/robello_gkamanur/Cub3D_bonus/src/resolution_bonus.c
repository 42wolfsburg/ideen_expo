/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:00:23 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 20:02:17 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	resolution_fits_screen(t_game *game, int w, int h)
{
	if (w > game->max_w || h > game->max_h)
	{
		printf("Error: %dx%d exceeds this screen's size! (%d x %d)\n",
			w, h, game->max_w, game->max_h);
		return (0);
	}
	return (1);
}

int	get_user_choice(void)
{
	char	input[10];
	int		choice;

	if (!fgets(input, sizeof(input), stdin))
		return (8);
	if (input[0] == '\n')
		return (8);
	choice = ft_atoi(input);
	if (choice < 1 || choice > 11)
		return (8);
	return (choice);
}

void	set_resolution_from_choice(t_game *game, int choice)
{
	int			index;
	const int	resolutions[][2] = {
	{640, 360}, {800, 450}, {960, 540},
	{1024, 576}, {1152, 648}, {1280, 720},
	{1366, 768}, {1600, 900}, {1920, 1080},
	{2560, 1440}, {3840, 2160}
	};

	index = choice - 1;
	if (index < 0 || index > 10)
		index = 7;
	game->win_w = resolutions[index][0];
	game->win_h = resolutions[index][1];
}

void	detect_screen_size(t_game *game)
{
	mlx_get_screen_size(game->mlx, &game->max_w, &game->max_h);
	if (game->max_w <= 0 || game->max_h <= 0)
	{
		game->max_w = 1920;
		game->max_h = 1080;
		printf("Note: Using default screen size:  1920 x 1080\n");
	}
	if (game->max_w > 7680)
		game->max_w = 7680;
	if (game->max_h > 4320)
		game->max_h = 4320;
}

void	setup_window_resolution(t_game *game)
{
	int	width;
	int	height;

	detect_screen_size(game);
	if (isatty(fileno(stdin)))
	{
		show_resolution_menu(game);
		game->res_choice = get_user_choice();
	}
	else
		game->res_choice = 8;
	set_resolution_from_choice(game, game->res_choice);
	set_speeds_for_resolution(game);
	width = game->win_w;
	height = game->win_h;
	if (!resolution_fits_screen(game, width, height))
		exit(1);
	warn_high_resolution(width, height);
	if (width >= 2560 && !get_confirmation())
		exit(0);
	game->win_h = (int)(width / ASPECT_RATIO);
	printf("  ✓ Resolution set to: %d x %d\n\n", game->win_w, game->win_h);
}
