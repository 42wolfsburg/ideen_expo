/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:13:29 by triedel           #+#    #+#             */
/*   Updated: 2024/01/17 19:35:11 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "display.h"

t_color	clt(unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	return ((t << 24) | (r << 16) | (g << 8) | (b));
}

t_color	cl(unsigned char r, unsigned char g, unsigned char b)
{
	return (clt(r, g, b, 0));
}

// t_color cl_combine(t_color c1, t_color c2)
// {
// 	unsigned char	r;
// 	unsigned char	g;
// 	unsigned char	b;

// 	r = (cl_opac(c1) * cl_red(c1) + cl_opac(c2) * cl_red(c2)) / 255;
// 	g = (cl_opac(c1) * cl_green(c1) + cl_opac(c2) * cl_green(c2)) / 255;
// 	b = (cl_opac(c1) * cl_blue(c1) + cl_opac(c2) * cl_blue(c2)) / 255;
// 	return cl(r, g, b);
// }

t_color	clt_to_cl(t_color c)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (cl_opac(c) * cl_red(c) / 255);
	g = (cl_opac(c) * cl_green(c) / 255);
	b = (cl_opac(c) * cl_blue(c) / 255);
	return (cl(r, g, b));
}

t_color	cl_add(t_color c1, t_color c2)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ft_min(cl_red(c1) + cl_red(c2), 255);
	g = ft_min(cl_green(c1) + cl_green(c2), 255);
	b = ft_min(cl_blue(c1) + cl_blue(c2), 255);
	return (cl(r, g, b));
}

t_color	cl_interpol(t_color from, t_color to, int i, int max)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	t;

	if (i > max || max == 0)
		return (to);
	t = cl_trans(from) + (i * (cl_trans(to) - cl_trans(from)) / max);
	r = cl_red(from) + (i * (cl_red(to) - cl_red(from)) / max);
	g = cl_green(from) + (i * (cl_green(to) - cl_green(from)) / max);
	b = cl_blue(from) + (i * (cl_blue(to) - cl_blue(from)) / max);
	return (clt(r, g, b, t));
}
