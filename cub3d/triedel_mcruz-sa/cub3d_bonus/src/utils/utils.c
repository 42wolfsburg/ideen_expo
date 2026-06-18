/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:50:52 by triedel           #+#    #+#             */
/*   Updated: 2024/08/13 12:57:27 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

/// If condition is true, return `true_val`, else return `false_val`
int	ft_ternary_int(bool condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}

/// If condition is true, return `true_val`, else return `false_val`
float	ft_ternary_float(bool cond, float true_val, float false_val)
{
	if (cond)
		return (true_val);
	return (false_val);
}

int	map_safe_ft_atoi(char *color)
{
	if (color == NULL || ft_strcmp(color, "\n") == 0)
	{
		ft_putstr_fd("Error: Invalid color input\n", 2);
		return (-1);
	}
	if (ft_strchr(color, '-') != NULL)
	{
		ft_putstr_fd("Error: Invalid color input: Negative values\n", 2);
		return (-1);
	}
	return (ft_atoi(color));
}

int	timediff(struct timeval *t1, struct timeval *t2)
{
	int	diff;

	diff = (t1->tv_sec - t2->tv_sec) * 1000;
	diff += (t1->tv_usec - t2->tv_usec) / 1000;
	return (diff);
}

void	*ft_xmalloc(size_t mem)
{
	void	*res;

	if (mem == 0)
		return (NULL);
	res = ft_calloc(mem, 1);
	if (!res)
		errexit("Malloc failed\n");
	return (res);
}
