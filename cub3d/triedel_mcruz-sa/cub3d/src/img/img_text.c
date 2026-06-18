/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:50:25 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 15:23:08 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	img_put_char(t_img *img, t_img *font, t_cpt dst, char ch)
{
	const char	c = ch - ' ';
	const int	y = c / 17;
	const int	x = c % 17;
	t_imgsec	src;

	src.sec = rect(x * FONT_CHAR_W, y * FONT_CHAR_H,
			(x + 1) * FONT_CHAR_W, (y + 1) * FONT_CHAR_H);
	src.img = font;
	img_put_img_section_stencil(img, &src, dst.pt, dst.col);
}

void	img_put_text(t_img *img, t_img *font, t_ipt dst, char *t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		img_put_char(img, font, cpt(CTEXT, dst.x + i * FONT_CHAR_W, dst.y), \
				t[i]);
		i++;
	}
}

void	img_put_text_extra(t_img *img, t_img *font, t_ipt dst, t_textinfo *t)
{
	t_cpt		c;
	int			i;

	i = 0;
	while (t->text[i] && i < t->pos)
	{
		c = cpt(t->color, dst.x + i * FONT_CHAR_W, dst.y);
		img_put_char(img, font, c, t->text[i]);
		i++;
	}
	if (t->carret)
	{
		c = cpt(t->color, dst.x + i * FONT_CHAR_W, dst.y);
		img_put_char(img, font, c, 127);
	}
}

void	img_put_text_center(t_img *img, t_img *font, t_ipt dst, char *text)
{
	const int	putx = dst.x - ft_strlen(text) * 15 / 2;
	const int	puty = dst.y - 15;

	img_put_text(img, font, ipt(putx, puty), text);
}

// void	img_put_textn(t_img *img, t_img *font,
// 			t_ipt dst, char *text, int n)
// {
// 	int		i;

// 	i = 0;
// 	while (text[i] && n--)
// 	{
// 		img_put_char(img, font, ipt(putx + i * FONT_CHAR_W, puty),
// 			text[i], CGREEN);
// 		i++;
// 	}
// 	img_put_char(img, font, ipt(putx + i * FONT_CHAR_W, puty),
//		127, CGREEN);//todo: do this properly?
// }
