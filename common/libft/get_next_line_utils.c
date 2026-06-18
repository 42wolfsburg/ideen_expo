/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:15:45 by triedel           #+#    #+#             */
/*   Updated: 2024/01/02 21:59:00 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// 0 -> failure
// 1 -> success
int	buffer_extend(t_buffer **buf)
{
	t_buffer	*newbuf;

	newbuf = malloc(sizeof(t_buffer));
	if (!newbuf)
		return (0);
	newbuf->pos = 0;
	newbuf->next = NULL;
	if (*buf)
		(*buf)->next = newbuf;
	*buf = newbuf;
	return (1);
}

void	*buffer_del(t_buffer *buf)
{
	t_buffer	*next;

	while (buf)
	{
		next = buf->next;
		free(buf);
		buf = next;
	}
	return (NULL);
}

t_buffer	*buffer_last(t_buffer *buf)
{
	t_buffer	*c;

	c = buf;
	while (c->next)
		c = c->next;
	return (c);
}

// 0 -> failure
// 1 -> success
int	buffer_feed(t_buffer **buf, char c)
{
	t_buffer	*cur;

	if (!*buf || (*buf)->pos >= BUFFER_SIZE)
		if (!buffer_extend(buf))
			return (0);
	cur = *buf;
	cur->data[cur->pos] = c;
	(cur->pos)++;
	return (1);
}

size_t	buffer_len(t_buffer *buf)
{
	size_t	len;

	len = 0;
	if (!buf)
		return (0);
	while (buf->next)
	{
		len += BUFFER_SIZE;
		buf = buf->next;
	}
	len += (buf->pos);
	return (len);
}

/*
#include <stdio.h>
void	buffer_print(t_buffer *buf)
{
	printf("buffer:\n");
	printf("pos is %i\n", buf->pos);
	write(1, buf->data, buf->pos);
	printf("\n\n");
}

void	filebuffer_print(struct s_filebuffer *s)
{
	printf("filebuffer:\n");
	printf("pos is %i, ", s->pos);
	printf("end is %i\n", s->end);
	printf("data is ");
	write(1, s->data + s->pos, s->end - s->pos);
	printf("\n\n");
}
*/
