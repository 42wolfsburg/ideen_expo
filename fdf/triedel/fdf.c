/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:30:21 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 12:11:43 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "load_fdf.h"

int	fdf_linelen(char *s)
{
	int		len;
	bool	inspace;

	len = 0;
	inspace = true;
	while (*s)
	{
		if (ft_isspace(*s))
			inspace = true;
		else
		{
			inspace && len++;
			inspace = false;
		}
		s++;
	}
	return (len);
}

void	fdf_line_del(void *arg)
{
	t_fdf_line	*line;

	line = (t_fdf_line *) arg;
	free(line->nodes);
	free(line);
}

void	fdf_getsize(t_fdf fdf, int *x, int *y)
{
	if (fdf)
		*x = ((t_fdf_line *) fdf->content)->len;
	else
		*x = 0;
	*y = ft_lstsize(fdf);
}

// void	fdf_print(t_fdf *fdf)
// {
// 	ft_printf("=== FDF ===\n");
// 	if (!*fdf)
// 	{
// 		ft_printf("NULL");
// 		return ;
// 	}
// 	ft_printf("fdf lstsize: %i\n", ft_lstsize(*fdf));
// 	ft_lstiter(*fdf, fdf_print_line);
// 	ft_printf("\n");
// }

// void	fdf_print_node(void *node)
// {
// 	t_node	*val;

// 	val = (t_node *) node;
// 	ft_printf("%i,%#x ", val->height, val->color);
// }

// void	fdf_print_line(void *arg)
// {
// 	t_fdf_line	*line;
// 	int			i;

// 	line = (t_fdf_line *) arg;
// 	i = 0;
// 	while (i < line->len)
// 		fdf_print_node(&line->nodes[i++]);
// }
