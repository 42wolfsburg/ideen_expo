/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_overlays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:56:52 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 13:55:32 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	game_draw_overlay_txt(t_game *game, char *msg)
{
	float	w;
	float	h;
	float	margin;
	t_ipt	tl;
	t_ipt	br;

	w = (ft_strlen(msg) + 2) * 15;
	h = 30;
	margin = .15 * w;
	tl = ipt(game->disp.width / 2 - w / 2 - margin, game->disp.height / 2
			- h / 2 - margin);
	br = ipt(game->disp.width / 2 + w / 2 + margin, game->disp.height / 2
			+ h / 2 + margin);
	img_draw_rect(&game->disp.buffer, tl, br, CRED);
	img_put_text_center(&game->disp.buffer, &game->textures[TXTFONT],
		ipt(game->disp.width / 2, game->disp.height / 2), msg);
}
