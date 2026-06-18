/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:45:28 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 23:08:56 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	handle_map_start(char *line, int *line_num, int *headers_found)
{
	if (*headers_found != 6)
	{
		printf("Error:  at .cub FILE line %d:\n",
			*line_num);
		printf("Line content: \"");
		print_escaped_line(line);
		printf("\"\n");
		printf("╔═════════════════════════════════════════════════════════╗\n");
		printf("║  Reason:    Map starts before all 6 headers are found   ║\n");
		printf("║             Found %d/6 headers (NO, SO, WE, EA, F, C)    ║\n",
			*headers_found);
		printf("╚═════════════════════════════════════════════════════════╝\n");
		return (0);
	}
	printf("  ✓ Map starts at FILE line %d\n", *line_num);
	return (1);
}

int	parse_cub_header(t_game *game, char *line, int *headers_found)
{
	char	*clean_line;
	char	*trimmed;
	int		result;

	clean_line = remove_carriage_returns(line);
	if (!clean_line)
		return (free(line), 0);
	trimmed = ft_strtrim(clean_line, " \t\n");
	free(clean_line);
	if (!trimmed)
		return (0);
	if (trimmed[0] == '\0')
		return (free(trimmed), 1);
	if (!validate_header_format(trimmed))
		return (free(trimmed), 0);
	result = process_header_line(game, trimmed, headers_found);
	free(trimmed);
	return (result);
}

int	is_empty_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_is_space(s[i]) && s[i] != '\n' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	reject_tabs_in_line(char *line, int line_num)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
		{
			printf("Error:  at .cub FILE line %d, col %d: TAB is not allowed\n",
				line_num, i);
			printf("Line content:  \"");
			j = -1;
			while (line[++j] && line[j] != '\n')
			{
				if (line[j] == '\t')
					printf("\\t");
				else if (line[j] == '\r')
					printf("\\r");
				else
					printf("%c", line[j]);
			}
			return (printf("\"\n"), 0);
		}
	}
	return (1);
}

int	process_header_line_wrapper(t_game *game, char *line, int *line_num,
		int *headers_found)
{
	int	parse_result;

	if (!reject_tabs_in_line(line, *line_num))
		return (0);
	if (is_empty_line(line))
		return (free(line), 1);
	parse_result = parse_cub_header(game, line, headers_found);
	if (parse_result == 0)
	{
		print_header_error(line, *line_num, "Invalid Header Format.");
		return (0);
	}
	if (parse_result == -1)
		return (handle_map_start(line, line_num, headers_found));
	free(line);
	return (1);
}
