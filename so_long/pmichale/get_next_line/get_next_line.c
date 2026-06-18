/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmichale <pmichale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:44:11 by pmichale          #+#    #+#             */
/*   Updated: 2024/01/30 18:38:03 by pmichale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/// @brief Reads a file descriptor with BUFFER_SIZE (default 4) 
/// @param fd File Descriptor
/// @return returns characters until "\n" is found
char	*get_next_line(int fd)
{
	static char	*stline;
	t_ls		ls;

	ls.offset = -1;
	if (fd >= 10240 || fd < 0)
		return (NULL);
	if (!stline)
	{
		stline = sub_calloc(BUFFER_SIZE + 1, sizeof(char));
		stline[0] = '\0';
	}
	stline = sub_handlestatic(fd, stline, &ls);
	return (ls.retline);
}

char	*sub_handlestatic(int fd, char *stline, t_ls *ls)
{
	int		i;

	i = 0;
	ls->done = 0;
	if (stline != NULL)
	{
		if (stline[0] != '\0')
		{
			while (stline[++ls->offset] != '\0' && ls->done == 0)
				if (stline[ls->offset] == '\n')
					ls->done++;
			if (ls->done == 1)
			{
				ls->retline = sub_newlinesep(stline, ls);
				stline = sub_buildstatic(stline, ls);
				return (stline);
			}
		}
	}
	ls->retline = sub_calloc(BUFFER_SIZE + 2 + ls->offset, sizeof(char));
	if (ls->offset == -1)
		ls->offset = 0;
	return (sub_mainloop(fd, stline, ls, i));
}

char	*sub_mainloop(int fd, char *stline, t_ls *ls, int i)
{
	int		j;

	while (ls->done == 0)
	{
		ls->line = sub_calloc(BUFFER_SIZE + 1, sizeof(char));
		j = read(fd, ls->line, BUFFER_SIZE);
		sub_staticinline(stline, ls, &i, &j);
		if (j == -1)
			return (free(ls->retline), ls->retline = NULL,
				free(ls->line), free(stline), NULL);
		j = 0;
		sub_retlinebuild(ls, &i, &j);
		if (ls->done != 0)
		{
			stline = sub_itssoover(ls, stline, &i, &j);
			if (ls->retline[0] == '\0')
				return (free(ls->retline), ls->retline = NULL,
					free(ls->line), stline);
			return (free(ls->line), stline);
		}
		ls->retline = sub_retlineextend(ls->retline);
		free(ls->line);
	}
	return ("GUHH????");
}

void	sub_retlinebuild(t_ls *ls, int *i, int *j)
{
	while (*j != BUFFER_SIZE && ls->done == 0 && ls->line[*j] != '\0')
	{
		if (ls->line[*j] == '\n')
			ls->done++;
		ls->retline[*i] = ls->line[*j];
		(*i)++;
		(*j)++;
	}
}

char	*sub_itssoover(t_ls *ls, char *stline, int *i, int *j)
{
	if (*j != BUFFER_SIZE + ls->offset)
	{
		*i = 0;
		while (ls->line[*j] != '\0')
		{
			stline[*i] = ls->line[*j];
			(*i)++;
			(*j)++;
		}
		stline[*i] = '\0';
	}
	if (ls->done >= 5)
		return (free(stline), NULL);
	return (stline);
}
