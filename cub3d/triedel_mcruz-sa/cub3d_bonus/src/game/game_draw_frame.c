/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:53:27 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 13:55:51 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	game_draw_crosshairs(t_game *game)
{
	int const	cw = game->disp.width / 2;
	int const	ch = game->disp.height / 2;
	int const	stroke = fmax(game->disp.height / 500.0, 1);
	int const	size = game->disp.height / 50;

	img_draw_rect(&game->disp.buffer, ipt(cw - stroke / 2, ch - size),
		ipt(cw + stroke / 2, ch - size / 4), CGREEN);
	img_draw_rect(&game->disp.buffer, ipt(cw - stroke / 2, ch + size / 4),
		ipt(cw + stroke / 2, ch + size), CGREEN);
	img_draw_rect(&game->disp.buffer, ipt(cw - size, ch - stroke / 2),
		ipt(cw - size / 4, ch + stroke / 2), CGREEN);
	img_draw_rect(&game->disp.buffer, ipt(cw + size / 4, ch - stroke / 2),
		ipt(cw + size, ch + stroke / 2), CGREEN);
}

void	game_draw_intro(t_game *game)
{
	char **const	intro = game->map.intro_phrases;
	const int		delay = 10;
	unsigned int	pos;
	unsigned int	i;
	t_textinfo		t;

	pos = game->ticks / 6;
	i = -1;
	while (intro[++i] && pos >= ft_strlen(intro[i]) + delay)
		pos -= ft_strlen(intro[i]) + delay;
	if (intro[i] && pos > ft_strlen(intro[i]) && \
			pos < ft_strlen(intro[i]) + delay)
		pos = ft_strlen(intro[i]);
	else if (!intro[i] || pos >= ft_strlen(intro[i]) + delay)
	{
		game->state = S_RUNNING;
		return ;
	}
	img_draw_rect(&game->disp.buffer, ipt(0, 0), ipt(game->disp.width,
			game->disp.height), CINTROBG);
	t = (t_textinfo){intro[i], CGREEN, pos, true};
	img_put_text_extra(&game->disp.buffer, &game->textures[TXTFONT],
		ipt(game->disp.width / 2 - (ft_strlen(intro[i]) * 15) / 2,
			game->disp.height / 2 - 15 / 2), &t);
}

void	game_draw_overlay_debug(t_game *game)
{
	char	t[30];
	char	*s;

	ft_strlcpy(t, "FPS: ", 30);
	s = ft_itoa(game->fps);
	ft_strlcat(t, s, 30);
	img_put_text(&game->disp.buffer, &game->textures[TXTFONT], ipt(10, 10),
		t);
	free(s);
	s = ft_itoa(game->rot / DEG);
	ft_strlcpy(t, "rot.: ", 30);
	ft_strlcat(t, s, 30);
	free(s);
	img_put_text(&game->disp.buffer, &game->textures[TXTFONT], ipt(10, 40),
		t);
	s = str_direction(angle_direction(game->rot));
	img_put_text(&game->disp.buffer, &game->textures[TXTFONT], ipt(10, 70),
		s);
	free(s);
}

void	game_draw_overlay_matrix(t_game *game)
{
	t_ipt	tl;
	t_ipt	br;

	img_put_img(&game->disp.buffer, &game->textures[TXTGUN],
		game->disp.width - game->textures[TXTGUN].width
		* game->textures[TXTGUN].scale, game->disp.height
		- game->textures[TXTGUN].height * game->textures[TXTGUN].scale);
	tl = ipt(0, game->disp.height - (float)game->disp.height / 200);
	br = ipt(game->disp.width * game->health / 75.0, game->disp.height);
	img_draw_rect(&game->disp.buffer, tl, br,
		col_mix(CRED, CGREEN, game->damage_taken));
	game->damage_taken = 0;
}

void	game_draw_frame(t_game *game)
{
	if (THREADS > 1)
		game_render_multi(game);
	else
		game_render(game);
	if (game->show_minimap)
		game_draw_minimap_direction(game);
	if (game->matrix_mode)
		game_draw_overlay_matrix(game);
	if (game->show_debug)
		game_draw_overlay_debug(game);
	game_draw_crosshairs(game);
	if (game->state == S_PAUSING || game->state == S_PAUSED)
		game_draw_overlay_txt(game, "PAUSED (p to unpause)");
	if (game->state == S_OVER)
		game_draw_overlay_txt(game, "GAME OVER");
	if (game->state == S_WON)
		game_draw_overlay_txt(game, "You won! (Esc to exit)");
}
