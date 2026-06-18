/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:52:55 by triedel           #+#    #+#             */
/*   Updated: 2024/08/06 09:52:58 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// Ensures value `val` is in between `min` and `max`, \returns adjusted value
float	fclamp(float val, float min, float max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}

/// Return `true` if `val` lies in between `min` and `max` (inclusively)
int	fbetw(float val, float min, float max)
{
	return (val >= min && val <= max);
}
