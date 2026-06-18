/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:44:17 by pmichale          #+#    #+#             */
/*   Updated: 2023/11/14 14:51:33 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/// @brief calls for memory and signs it with 0's
/// @param count how much memory
/// @param size the size of each block of memory
/// @return returns the allocated memory
void	*sub_calloc(size_t count, size_t size)
{
	void			*memory;
	size_t			i;
	unsigned char	*mcpy;

	memory = malloc(size * count);
	if (!memory)
		return (0);
	mcpy = (unsigned char *)memory;
	i = 0;
	while (i < size * count)
		mcpy[i++] = (unsigned char)0;
	return (memory);
}

char	*sub_newlinesep(char *line, t_ls *ls)
{
	char	*sepline;
	int		i;

	sepline = sub_calloc(ls->offset + 1, sizeof(char));
	i = 0;
	while (i != ls->offset)
	{
		sepline[i] = line[i];
		i++;
	}
	return (sepline);
}

char	*sub_buildstatic(char *stline, t_ls *ls)
{
	int		i;
	int		j;
	char	*sepline;

	sepline = sub_calloc(BUFFER_SIZE + 1, sizeof(char));
	i = 0;
	while (stline[i] != '\0')
		i++;
	if (i - ls->offset == 0)
	{
		sepline[0] = '\0';
		return (free(stline), sepline);
	}
	j = ls->offset;
	i = 0;
	while (stline[j] != '\0')
	{
		sepline[i] = stline[j];
		j++;
		i++;
	}
	sepline[i] = '\0';
	return (free(stline), stline = NULL, sepline);
}

char	*sub_retlineextend(char *retline)
{
	int		i;
	char	*newline;

	i = 0;
	while (retline[i] != '\0')
		i++;
	newline = sub_calloc(i + BUFFER_SIZE + 1, sizeof(char));
	i = 0;
	while (retline[i] != '\0')
	{
		newline[i] = retline[i];
		i++;
	}
	newline[i] = '\0';
	return (free(retline), newline);
}

void	sub_staticinline(char *stline, t_ls *ls, int *i, int *j)
{
	if (*j == 0)
		ls->done = 5;
	if (j == 0)
		ls->done = 5;
	if (stline != NULL)
	{
		if (stline[0] != '\0')
		{
			while (stline[*i] != '\0')
			{
				ls->retline[*i] = stline[*i];
				(*i)++;
			}
			stline[0] = '\0';
		}
	}
}
