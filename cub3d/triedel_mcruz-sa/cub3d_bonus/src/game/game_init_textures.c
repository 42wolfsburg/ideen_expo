/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:15:32 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 14:49:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <mlx.h>

void	game_obj_new(t_game *game, t_objtype type, t_vec3 *pos)
{
	t_obj	nobj;

	nobj.type = type;
	nobj.pos = *pos;
	if (type == OBJ_AGENT)
	{
		nobj.width = .5 * .8;
		nobj.height = .8;
		nobj.u_obj.enemy.hit_points = 100;
	}
	else if (type == OBJ_PHONEBOX)
	{
		nobj.width = .5;
		nobj.height = 1;
	}
	else if (type == OBJ_PILL)
	{
		nobj.width = .25;
		nobj.height = .1;
		nobj.normal = vec(1, 0);
	}
	else if (type == OBJ_DOOR)
		game_obj_door_init(game, &nobj, pos);
	game_obj_add(game, &nobj);
}

void	game_obj_door_init(t_game *game, t_obj *nobj, t_vec3 *pos)
{
	nobj->width = 1;
	nobj->height = 1;
	if (map_get(&game->map, pos->x + 1, pos->y) == '1'
		&& map_get(&game->map, pos->x - 1, pos->y) == '1')
		nobj->normal = vec(0, 1);
	else
		nobj->normal = vec(1, 0.001);
	nobj->texture_id = 4;
	nobj->u_obj.door.open = 0;
	nobj->u_obj.door.state = D_CLOSED;
}

/// Load all game textures
int	game_init_textures(t_game *game)
{
	int		i;
	char	*txt;
	int		a;

	game->textures = ft_xmalloc(sizeof(t_img) * (TXTMAX + 1
				+ game->map.txtcount - 4));
	game_init_img_textures(game);
	i = -1;
	while (++i < game->map.txtcount)
	{
		txt = game->map.map_textures[i];
		a = TXTMAX + 1 + i - 4;
		if (i < 4)
			a = i;
		if (access(txt, F_OK) != 0)
		{
			ft_putstr_fd(txt, STDERR_FILENO);
			game_deinit(game);
			errexit(": Texture file not accessible\n");
		}
		img_load(&game->textures[a], game->disp.mlx, txt);
	}
	return (OK);
}

void	game_init_img_textures(t_game *game)
{
	game_txt_load(game, TXTDOOR, "assets/door.xpm");
	game_txt_load(game, TXTAGENT0, "assets/smith0.xpm");
	game_txt_load(game, TXTAGENT1, "assets/smith1.xpm");
	game_txt_load(game, TXTAGENT2, "assets/smith2.xpm");
	game_txt_load(game, TXTPILL, "assets/pill.xpm");
	game_txt_load(game, TXTPHONEBOX0, "assets/phonebox.xpm");
	game_txt_load(game, TXTPHONEBOX1, "assets/phonebox2.xpm");
	game_txt_load(game, TXTPOINT, "assets/point.xpm");
	game_txt_load(game, TXTGUN, "assets/gun20.xpm");
	game->textures[TXTGUN].scale = 0.8;
	game_txt_load(game, TXTBOX, "assets/box.xpm");
	game_txt_load(game, TXTFONT, "assets/font.xpm");
	game_txt_load(game, TXTBULLET, "assets/bullet.xpm");
	game_txt_load(game, TXTFLOOR, "textures/wood.xpm");
}

void	game_map_add_objects(t_game *game)
{
	t_vec3		pos;
	t_objtype	type;
	int			x;
	int			y;

	x = 0;
	while (x < game->map.width)
	{
		y = 0;
		while (y < game->map.height)
		{
			pos = vec3(x + .5, y + .5, 0);
			type = map_char_to_objtype(map_get(&game->map, x, y));
			if (type != OBJ_NONE)
			{
				game_obj_new(game, type, &pos);
				map_set(&game->map, x, y, '0');
			}
			y++;
		}
		x++;
	}
}
