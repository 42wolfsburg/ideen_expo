/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:19:28 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 15:52:24 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <libft.h>
#include "display.h"
#include "load_fdf.h"

#define RES_NONE	-1
#define RES_DONE	-2
#define RES_ERROR	-3

t_fdf	*fdf_load(int fd, t_fdf *fdf)
{
	int		state;

	*fdf = NULL;
	state = RES_NONE;
	while (state == RES_NONE || state > 0)
		state = fdf_read_line(fd, fdf, state);
	if (state < 0 && state != RES_DONE)
		return ((t_fdf *)(ft_lstclear_null(fdf, fdf_line_del), NULL));
	return (fdf);
}

bool	fdf_read_value(const char **s, t_node *value)
{
	value->height = ft_atoi_ref(s);
	value->color = C_FDF;
	if (ft_strncmp(*s, ",0x", 3) == 0)
	{
		*s += 3;
		value->color = ft_atoi_hex_ref(s);
	}
	return (true);
}

int	fdf_line_fill(const char *s, t_fdf_line *line)
{
	bool	inspace;
	int		i;

	i = 0;
	inspace = true;
	while (i < line->len && *s && *s != '\n')
	{
		if (ft_isspace(*s))
			inspace = true;
		else
			if (inspace)
				if (!fdf_read_value(&s, &line->nodes[i++]))
					return (RES_ERROR);
		s++;
	}
	while (i < line->len)
		line->nodes[i++] = (t_node){.height = 0, .color = C_FDF};
	return (i);
}

int	fdf_read_line(int fd, t_fdf *fdf, int len)
{
	char		*linestr;
	t_fdf_line	*line;
	t_list		*n;

	linestr = get_next_line(fd);
	if (!linestr)
		return (0);
	line = malloc(sizeof(t_fdf_line));
	if (!line)
		return (free(line), free(linestr), RES_ERROR);
	if (len == RES_NONE)
		line->len = fdf_linelen(linestr);
	else
		line->len = len;
	line->nodes = malloc(sizeof(t_node) * line->len);
	if (!line->nodes)
		return (free(line), free(linestr), RES_ERROR);
	if (fdf_line_fill(linestr, line) != line->len)
		return (free(line->nodes), free(line), free(linestr), -1);
	free(linestr);
	n = ft_lstnew((void *) line);
	if (!n)
		return (free(line), RES_ERROR);
	ft_lstadd(fdf, n);
	return (line->len);
}
