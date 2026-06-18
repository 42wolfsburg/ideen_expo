/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:46:46 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 14:42:36 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_color	col_lum(t_color c, float f)
{
	const int	r = f * (0xff & (c >> 16));
	const int	g = f * (0xff & (c >> 8));
	const int	b = f * (0xff & c);

	return ((c & 0xff000000) + (r << 16) + (g << 8) + b);
}

/// Fade `color` to black with increasing distance `dist`
t_color	col_fade(t_color color, float dist)
{
	const float	f = fclamp((25 - (dist - 10)) / 25, .25, 1);

	color = col_lum(color, f);
	return (color);
}

t_color	col_mix(t_color a, t_color b, float mix)
{
	const t_color	ar = (a & 0xff0000) * mix;
	const t_color	ag = (a & 0xff00) * mix;
	const t_color	ab = (a & 0xff) * mix;
	const t_color	br = (b & 0xff0000) * (1 - mix);
	const t_color	bg = (b & 0xff00) * (1 - mix);

	return ((ar & 0xff0000) | (ag & 0x00ff00) | (ab & 0x0000ff) | \
		(br & 0xff0000) | (bg & 0x00ff00) | \
		((int)((b & 0xff) * (1 - mix)) & 0x0000ff));
}

t_color	col_apply(t_color col_orig, t_color col_apply)
{
	if (col_apply != CTRANSPARENT)
		return (col_apply);
	return (col_orig);
}
