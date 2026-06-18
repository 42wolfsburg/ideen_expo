/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_chns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:30:54 by triedel           #+#    #+#             */
/*   Updated: 2024/01/17 19:35:39 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

unsigned char	cl_trans(t_color c)
{
	return ((c >> 24) & 0xff);
}

unsigned char	cl_opac(t_color c)
{
	return (255 - cl_trans(c));
}

unsigned char	cl_red(t_color c)
{
	return ((c >> 16) & 0xff);
}

unsigned char	cl_green(t_color c)
{
	return ((c >> 8) & 0xff);
}

unsigned char	cl_blue(t_color c)
{
	return (c & 0xff);
}
