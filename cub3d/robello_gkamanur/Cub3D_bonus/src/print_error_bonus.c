/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:55:45 by robello           #+#    #+#             */
/*   Updated: 2026/01/25 18:16:47 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	print_reachable_map_debug(char **map, char **reachable, int dims[2])
{
	int	i;
	int	j;

	printf("\n  === Reachable Map ===\n");
	i = 0;
	while (i < dims[0])
	{
		printf("%3d: ", i);
		j = 0;
		while (j < dims[1])
		{
			if (reachable[i][j] == 'R')
				printf("R");
			else
				printf("%c", map[i][j]);
			j = j + 1;
		}
		printf("\n");
		i = i + 1;
	}
}

void	print_char_error(char c, int file_line, int col)
{
	printf("\nError in .cub FILE, line %d, col %d: ", file_line, col);
	if (c == '\t')
		printf("TAB character not allowed\n");
	else if (c == '\r')
		printf("CARRIAGE RETURN character not allowed\n");
	else
		printf("Invalid character '%c'\n", c);
}

void	print_empty_line_error(int file_line, int is_first)
{
	if (is_first)
		printf("Error:  at FILE line %d: Empty line inside map\n", file_line);
	else
		printf("Error:  in .cub FILE line %d Empty line inside map\n",
			file_line);
}

void	print_map_error(char *reason)
{
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║		Error:  %s              ║\n", reason);
	printf("║		Reason: See detailed error above           ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n");
}

void	print_header_error(char *line, int line_num, char *reason)
{
	int	k;

	printf("Error:  at FILE line %d:\n", line_num);
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║     Line content:   \"");
	k = 0;
	while (line[k] && line[k] != '\n')
	{
		if (line[k] == '\t')
			printf("\\t");
		else if (line[k] == '\r')
			printf("\\r");
		else
			printf("%c", line[k]);
		k = k + 1;
	}
	printf("\"           ║\n");
	printf("║     Reason:        %s", reason);
	printf("                ║\n");
	printf("╚══════════════════════════════════════════════════════════╝\n");
}
