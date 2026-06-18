/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jastomme <jastomme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:33:45 by jastomme          #+#    #+#             */
/*   Updated: 2024/12/09 11:00:06 by jastomme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	stash = stash_filling(fd, stash, buffer);
	if (stash && *stash == 0)
	{
		free(stash);
		return (stash = 0);
	}
	line = extract_line(stash, line);
	stash = extract_new_stash(stash);
	return (line);
}

char	*stash_filling(int fd, char *stash, char *buffer)
{
	ssize_t	nbytes;
	char	*temp;

	nbytes = 1;
	if (stash == NULL)
		stash = ft_strdup("");
	while (nbytes > 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[nbytes] = 0;
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
		if ((ft_strchr(buffer, '\n')))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*extract_new_stash(char *stash)
{
	int		len;
	char	*new_stash;

	len = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[len] != '\n' && stash[len] != '\0')
		len++;
	if (stash[len] == '\n')
		len++;
	new_stash = malloc((ft_strlen(stash) - len + 1) * sizeof(char));
	if (new_stash == NULL)
		return (NULL);
	ft_strlcpy(new_stash, stash + len, ft_strlen(stash) - len + 1);
	free(stash);
	return (new_stash);
}

char	*extract_line(char *stash, char *line)
{
	size_t	len;

	len = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[len] != '\n' && stash[len] != '\0')
		len++;
	if (stash [len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, stash, len + 1);
	return (line);
}
