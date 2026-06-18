/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:24:17 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 10:31:25 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

bool	rect_inside(t_rect *rect, t_pt pt)
{
	return (pt.x >= rect->tl.x && pt.x <= rect->br.x && \
			pt.y >= rect->tl.y && pt.y <= rect->br.y);
}
