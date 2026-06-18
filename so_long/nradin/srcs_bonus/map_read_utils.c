/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:54:16 by nradin            #+#    #+#             */
/*   Updated: 2023/03/03 14:31:56 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	count_lines(int fd)
{
	int		i;
	char	*s;

	i = 0;
	s = get_next_line(fd);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
		i++;
	}
	return (i);
}

char	**read_map(t_game *game, char	*map)
{
	char	**res;
	int		fd;
	char	*s;
	int		i;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		throw_error(game, NULL, FILE_ERROR);
	res = ft_calloc(sizeof(char *), count_lines(fd) + 1);
	if (!res)
		return (NULL);
	close(fd);
	fd = open(map, O_RDONLY);
	s = get_next_line(fd);
	i = 0;
	while (s)
	{
		res[i] = s;
		s = get_next_line(fd);
		i++;
	}
	res[i] = 0;
	close(fd);
	return (res);
}
