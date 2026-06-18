/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:41:14 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 12:41:19 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// Ensure `angle` lies in between [0,2*M_PI)
float	angle_normalize(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	angle_direction(float angle)
{
	const float	deg = angle_normalize(angle) / DEG;

	if (fbetw(deg, 0, 45) || fbetw(deg, 315, 360))
		return (DNORTH);
	else if (fbetw(deg, 45, 135))
		return (DWEST);
	else if (fbetw(deg, 135, 225))
		return (DSOUTH);
	else if (fbetw(deg, 225, 315))
		return (DEAST);
	return (-1);
}

float	rot_fromchar(char o)
{
	if (o == 'N')
		return (0);
	if (o == 'S')
		return (M_PI);
	if (o == 'W')
		return (M_PI / 2);
	if (o == 'E')
		return (M_PI / 2 * 3);
	return (0);
}

char	*str_direction(int d)
{
	if (d == DNORTH)
		return (ft_strdup("NORTH"));
	else if (d == DWEST)
		return (ft_strdup("WEST"));
	else if (d == DSOUTH)
		return (ft_strdup("SOUTH"));
	else if (d == DEAST)
		return (ft_strdup("EAST"));
	return (NULL);
}
