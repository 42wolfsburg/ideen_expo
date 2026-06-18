/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:30:18 by triedel           #+#    #+#             */
/*   Updated: 2024/08/12 15:31:27 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE	1024

/// Reads through file `path` and returns its length
int	ft_filelen(char *path)
{
	int		fd;
	char	buffer[BUFSIZE];
	int		readres;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ERR);
	len = 0;
	while (1)
	{
		readres = read(fd, buffer, BUFSIZE);
		if (readres <= 0)
			break ;
		len += readres;
	}
	close(fd);
	if (readres < 0)
		return (ERR);
	return (len);
}

/// Return file `path` as string, setting `datalen` to the number of bytes
/// in the file
char	*ft_fileload(char *path, int *datalen)
{
	const int	len = ft_filelen(path);
	int			fd;
	int			readres;
	int			pos;
	char		*data;

	data = ft_xmalloc(sizeof(char) * (len + 1));
	data[len] = '\0';
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (datalen)
		*datalen = len;
	pos = 0;
	while (1)
	{
		readres = read(fd, &data[pos], BUFSIZE);
		if (readres <= 0)
			break ;
		pos += readres;
	}
	close(fd);
	if (readres < 0)
		return (free(data), NULL);
	return (data);
}
