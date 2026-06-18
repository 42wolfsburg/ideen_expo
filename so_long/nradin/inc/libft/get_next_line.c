/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:44:50 by nradin            #+#    #+#             */
/*   Updated: 2023/02/02 13:17:26 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL)
		res = ft_strjoin_gnl("", s2);
	else
	{
		res = ft_strjoin_gnl(s1, s2);
		free(s1);
	}
	return (res);
}

char	*ft_trim_start(char *str)
{
	size_t	i;
	char	*t;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || !str[i + 1])
	{
		free(str);
		return (NULL);
	}
	t = ft_substr_gnl(str, i + 1, ft_strlen_gnl(str) - i - 1);
	free(str);
	return (t);
}

char	*ft_trim_end(char *str)
{
	size_t	i;
	char	*t;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	t = ft_substr_gnl(str, 0, i + 1);
	return (t);
}

char	*read_from_file(int fd, char *res)
{
	int		byte_read;
	char	*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	byte_read = read(fd, buf, BUFFER_SIZE);
	while (byte_read != 0)
	{
		if (byte_read == -1)
		{
			if (res)
				free(res);
			free(buf);
			return (NULL);
		}
		buf[byte_read] = 0;
		res = ft_strjoin_free(res, buf);
		if (ft_strrchr_gnl(buf, '\n'))
			break ;
		byte_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buf[65536];
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (buf[fd])
			free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	if (!ft_strrchr_gnl(buf[fd], '\n'))
		buf[fd] = read_from_file(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	res = ft_trim_end(buf[fd]);
	buf[fd] = ft_trim_start(buf[fd]);
	return (res);
}
