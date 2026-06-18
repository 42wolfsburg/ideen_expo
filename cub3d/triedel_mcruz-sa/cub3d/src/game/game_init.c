/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:49:46 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 15:09:31 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <mlx.h>
#include <pthread.h>

void	game_map_add_planes(t_game *game)
{
	int		i;
	t_obj	*o;

	i = 0;
	while (i < game->map.objcount)
	{
		o = &game->map.obj[i];
		if (o->width == 0)
			o->width = o->height * ((float)game->textures[TXTMAX + 1
					+ o->texture_id].width / game->textures[TXTMAX + 1
					+ o->texture_id].height);
		if (o->height == 0)
			o->height = o->width * ((float)game->textures[TXTMAX + 1
					+ o->texture_id].height / game->textures[TXTMAX + 1
					+ o->texture_id].width);
		game_obj_add(game, &game->map.obj[i]);
		i++;
	}
}

/*
void	game_init_logic(t_game *game)
{
	game->pos = vec3(game->map.spawn_x + .5, game->map.spawn_y + .5, 0);
	game->mz = 0;
	game->rot = rot_fromchar(game->map.direction);
	ft_bzero(&game->input_state, 64);
	game->ticks = 0;
	game->health = 75;
	game->matrix_mode = MATTEX;
	game->matrix_mode_mix = 0;
	game->show_minimap = 1;
	game->physics = 1;
	game->show_debug = 1;

	game->damage_taken = 0;
	game->state = S_INTRO;

	game_map_add_objects(game);
	game_map_add_planes(game);
}

void	game_init_camera(t_game *game)
{
	size_t	hl_size;
	size_t	hl_num;

	game->last_draw.tv_sec = 0;
	game->last_draw.tv_usec = 0;
	game->fov = M_PI / 2;
	game->rotx = 0;
	game->upscale = GAME_UPSCALE;
	game->cam_width = CAM_WIDTH;
	game_calc_camera_params(game);
	game_mouse_trap(game);
	hl_size = sizeof(t_column_data);
	hl_num = ceil(game->disp.width / (float) game->upscale);
	game->hit_buffer = malloc(hl_size * hl_num);
}


/// Load all game textures
int	game_init_textures(t_game *game)
{
	int		i;
	char	*txt;
	int		a;

	game->textures = \
			ft_xmalloc(sizeof(t_img) * ((TXTMAX + 1) + game->map.txtcount - 4));
	img_load(&game->textures[TXTDOOR], game->disp.mlx, "assets/door.xpm");
	img_load(&game->textures[TXTAGENT0], game->disp.mlx, "assets/smith0.xpm");
	img_load(&game->textures[TXTAGENT1], game->disp.mlx, "assets/smith1.xpm");
	img_load(&game->textures[TXTAGENT2], game->disp.mlx, "assets/smith2.xpm");
	img_load(&game->textures[TXTPILL], game->disp.mlx, "assets/pill.xpm");
	img_load(&game->textures[TXTDOOR], game->disp.mlx, "assets/door.xpm");
	img_load(&game->textures[TXTPHONEBOX0], \
		game->disp.mlx, "assets/phonebox.xpm");
	img_load(&game->textures[TXTPHONEBOX1], \
		game->disp.mlx, "assets/phonebox2.xpm");
	img_load(&game->textures[TXTPOINT], game->disp.mlx, "assets/point.xpm");
	img_load(&game->textures[TXTGUN], game->disp.mlx, "assets/gun20.xpm");
	game->textures[TXTGUN].scale = 0.8;
	img_load(&game->textures[TXTBOX], game->disp.mlx, "assets/box.xpm");
	img_load(&game->textures[TXTFONT], game->disp.mlx, "assets/font.xpm");
	img_load(&game->textures[TXTBULLET], game->disp.mlx, "assets/bullet.xpm");
	img_load(&game->textures[TXTFLOOR], game->disp.mlx, "textures/wood.xpm");
	img_init(&game->minimap, game->disp.mlx, 500, 500);
	img_init(&game->mattex, game->disp.mlx, MATTEX_SIZE, MATTEX_SIZE);
	if (mattex_init(&game->mt) != OK)
		return (ERR);
	i = 0;
	while (i < game->map.txtcount)
	{
		txt = game->map.map_textures[i];
		a = TXTMAX + i - 3;
		if (i < 4)
			a = i;
		img_load(&game->textures[a], game->disp.mlx, txt);
		i++;
	}
	mattex_draw(&game->mt, game, &game->mattex);
	return (OK);
}
*/

void	game_txt_load(t_game *game, int txtid, char *path)
{
	if (!img_load(&game->textures[txtid], game->disp.mlx, path))
	{
		game_deinit(game);
		errexit("Loading image failed\n");
	}
}

/// Set up mlx event hooks
void	game_init_hooks(t_game *game)
{
	mlx_hook(game->disp.win, KeyPress, KeyPressMask, game_keydown, game);
	mlx_hook(game->disp.win, KeyRelease, KeyReleaseMask, game_keyup, game);
	mlx_hook(game->disp.win, ButtonPress, ButtonPressMask, game_mousedown,
		game);
	mlx_expose_hook(game->disp.win, (int (*)(void *))game_expose, game);
	mlx_loop_hook(game->disp.mlx, (int (*)(void *))game_loop, game);
}

/// Initialize new map - this needs to be called on map switch
void	game_init_map(t_game *game, char *map_path)
{
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->objects, MAX_OBJECTS * sizeof(t_obj));
	map_init_values(&game->map);
	map_read(&game->map, map_path);
	game_init_textures(game);
	game_init_logic(game);
}

/// Initialize and run game
void	game_init(t_game *game, char *map_path, int w, int h)
{
	ft_bzero(game, sizeof(t_game));
	display_init(&game->disp, w, h);
	game_init_hooks(game);
	game->minimap_rect = rect(MINIMAP_TLX, MINIMAP_TLY,
			MINIMAP_BRX, MINIMAP_BRY);
	game->minimap_center = ipt(
			(game->minimap_rect.br.x + game->minimap_rect.tl.x) / 2,
			(game->minimap_rect.br.y + game->minimap_rect.tl.y) / 2);
	mattex_init(&game->mt);
	game_init_map(game, map_path);
	img_init(&game->mattex, game->disp.mlx, MATTEX_SIZE, MATTEX_SIZE);
	mattex_draw(&game->mt, game, &game->mattex);
	game_init_camera(game);
	pthread_mutex_init(&game->mutex_render, NULL);
	game_setup_window_close_handler(game->disp.win);
	mlx_loop(game->disp.mlx);
}
