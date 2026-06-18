/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:17:08 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 14:33:16 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <mlx.h>

void	game_obj_print(t_obj *obj)
{
	printf("game object: \n");
	printf("pos: %.2f %.2f %.2f\n", obj->pos.x, obj->pos.y, obj->pos.z);
	printf("dim: %.2fx%.2f\n", obj->width, obj->height);
	printf("normal: %.2fx%.2f\n", obj->normal.x, obj->normal.y);
	printf("txtID: %i\n", obj->texture_id);
}

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
	hl_num = ceil(game->disp.width / (float)game->upscale);
	game->hit_buffer = ft_xmalloc(hl_size * hl_num);
}

t_objtype	map_char_to_objtype(char objchar)
{
	if (objchar == 'A')
		return (OBJ_AGENT);
	else if (objchar == 'P')
		return (OBJ_PHONEBOX);
	else if (objchar == 'R')
		return (OBJ_PILL);
	else if (objchar == 'D')
		return (OBJ_DOOR);
	return (OBJ_NONE);
}
