/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:45:52 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 18:53:38 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	print_unreachable_error(int i, int j, char c)
{
	printf("Error: Unreachable entity/area map@ [%d,%d]\n",
		i, j + 1);
	printf("       Character '%c' cannot be reached by the player.\n", c);
}

void	print_row_chars(char *row)
{
	int		j;
	char	c;

	j = 0;
	while (row[j])
	{
		c = row[j];
		if (c == '\t')
			printf("\\t");
		else if (c == '\n')
			printf("\\n");
		else if (c == ' ')
			printf("·");
		else
			printf("%c", c);
		j = j + 1;
	}
}

void	print_map_debug(char **map, const char *label)
{
	int	i;

	printf("\n  === %s ===\n", label);
	if (!map)
	{
		printf("(NULL)\n");
		return ;
	}
	i = 0;
	while (map[i])
	{
		printf("%3d: ", i);
		print_row_chars(map[i]);
		printf("\n");
		i = i + 1;
	}
	printf("  === END %s ===\n", label);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		write(1, map[i], ft_strlen(map[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	print_escaped_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '\t')
			printf("\\t");
		else if (line[i] == '\r')
			printf("\\r");
		else
			printf("%c", line[i]);
		i = i + 1;
	}
}
