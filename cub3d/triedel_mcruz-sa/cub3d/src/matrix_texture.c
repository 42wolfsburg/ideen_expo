/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:53:35 by triedel           #+#    #+#             */
/*   Updated: 2024/08/12 15:31:32 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <fcntl.h>
#include <stdlib.h>

int	mattex_init(t_mattex *m)
{
	int	i;

	i = 0;
	while (i < MATTEX_SYMS)
		m->pts[i++] = (t_pt2){rand() % MATTEX_SIZE, rand() % MATTEX_SIZE};
	m->data = ft_fileload("assets/src.all", &m->datalen);
	return (OK);
}

void	mattex_update(t_mattex *m)
{
	int	i;

	i = 0;
	while (i < MATTEX_SYMS)
	{
		m->pts[i].y += MATTEX_FONT_H;
		if (m->pts[i].y >= MATTEX_SIZE)
		{
			m->pts[i].x = rand() % MATTEX_SIZE;
			m->pts[i].y = -30 - rand() % 30;
		}
		i++;
	}
}

char	random_char(t_mattex *mt, int col)
{
	if (col <= 0)
		col = -col + 1;
	col = col % mt->datalen;
	return (mt->data[col]);
}

void	mattex_draw(t_mattex *m, t_game *game, t_img *img)
{
	t_cpt	cpt;
	int		i;
	int		charpick;

	img_green_fade(img);
	i = 0;
	while (i < MATTEX_SYMS)
	{
		cpt = (t_cpt){MATTEX_WHITE, ipt(m->pts[i].x, m->pts[i].y)};
		charpick = (int) m->pts[i].x + (int) m->pts[i].y / MATTEX_FONT_H;
		img_put_char(img, &game->textures[TXTFONT], cpt,
			random_char(m, charpick));
		i++;
	}
}
