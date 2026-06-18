/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_fdf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:05:55 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 15:52:34 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_FDF_H
# define LOAD_FDF_H

# include <stdlib.h>
# include <stdint.h>

# include <libft.h>

typedef uint32_t	t_color;
typedef t_list		*t_fdf;

typedef struct s_node
{
	int		height;
	t_color	color;
}	t_node;

typedef struct s_fdf_line
{
	int		len;
	t_node	*nodes;
}	t_fdf_line;

/* $$proto_start$$ */

/* load_fdf.c */
t_fdf	*fdf_load(int fd, t_fdf *fdf);
int		fdf_linelen(char *s);
bool	fdf_read_value(const char **s, t_node *value);
int		fdf_line_fill(const char *s, t_fdf_line *line);
void	fdf_line_del(void *arg);
int		fdf_read_line(int fd, t_fdf *fdf, int len);
void	fdf_getsize(t_fdf fdf, int *x, int *y);
void	fdf_print_node(void *node);
void	fdf_print_line(void *arg);
void	fdf_print(t_fdf *fdf);

/* $$proto_end$$ */

#endif