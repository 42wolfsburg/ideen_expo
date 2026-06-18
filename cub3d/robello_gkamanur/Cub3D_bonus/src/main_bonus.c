/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:40:41 by robello           #+#    #+#             */
/*   Updated: 2026/01/08 22:40:41 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_init_game_struct(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->game_time = 0.0;
	game->flash = 0;
	game->game_won = 0;
	ft_init_colors(game);
	game->enemy_anim_frames = 15;
	game->coll_anim_frames = 10;
	game->res_choice = 8;
	game->bonus.s_collision.enabled = 1;
	game->bonus.s_minimap.enabled = 1;
	game->bonus.s_mouse.enabled = 1;
	game->player.play_x = -1;
	game->player.play_y = -1;
	game->player.move_speed = MOVE_SPEED;
	game->player.rota_speed = ROTA_SPEED;
	game->bonus.s_collision.radius = COLL_RADIUS;
	game->bonus.s_minimap.scale = MINIMAP_SCALE;
	game->bonus.s_minimap.offset_x = MINIMAP_OFFSET_X;
	game->bonus.s_minimap.offset_y = MINIMAP_OFFSET_Y;
	game->bonus.s_mouse.sensitivity = MOUSE_SENS;
	game->gmover.state = GAME_RUNNING;
	game->gmover.fading = 0;
	ft_init_systems_struct(game);
}

void	ft_display_game_info(t_game *game)
{
	printf("\n══════════════════════════════════════════\n");
	printf("    ENJOY AND HAVE FUN WITH \"MAD LAB3D\"");
	printf("\n══════════════════════════════════════════\n");
	printf("   ==========  GAME READY  =========\n");
	printf("   -Window:  %dx%d\n", game->win_w, game->win_h);
	printf("   -Map:     %dx%d\n", game->map.height, game->map.width);
	printf("   -Controls 🎮 :\n\n");
	printf("         W  A  S  D	Move\n");
	printf("         ← / →		Rotate\n");
	printf("         Mouse		Look around\n");
	printf("         ALT+TAB	Free mouse\n");
	printf("         SPACE BAR	Open door\n");
	printf("         ESC		Exit\n");
	printf("\n══════════════════════════════════════════\n");
	printf("    ENJOY AND HAVE FUN WITH \"MAD LAB3D\"");
	printf("\n══════════════════════════════════════════\n\n");
}

int	ft_init_graphics(t_game *game)
{
	allocate_sprite_list(game);
	setup_window_resolution(game);
	if (!main_load_bonus_textures(game))
	{
		ft_putstr_fd("Error:  Failed to load textures\n", 2);
		return (0);
	}
	if (!create_game_window(game))
		return (0);
	return (1);
}

int	ft_init_mlx_and_parse(t_game *game, int fd)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		close(fd);
		ft_putstr_fd("Error:  MLX initialization failed\n", 2);
		return (0);
	}
	if (!parse_cub_file(fd, game))
	{
		close(fd);
		ft_putstr_fd("Error:  Parsing failed\n\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	if (ac != 2)
	{
		write(2, "Error: Usage: ./cub3d-bonus <map.cub>\n", 39);
		return (1);
	}
	fd = validate_input(av);
	if (fd < 0)
		return (1);
	ft_init_game_struct(&game);
	if (!ft_init_mlx_and_parse(&game, fd))
		return (ft_cleanup_game(&game), 1);
	if (!ft_init_graphics(&game))
		return (ft_cleanup_game(&game), 1);
	ft_display_game_info(&game);
	ft_setup_hooks(&game);
	ft_render_frame(&game);
	mlx_loop(game.mlx);
	ft_cleanup_game(&game);
	return (0);
}
