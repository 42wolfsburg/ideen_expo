/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmorvai <bmorvai@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:31:41 by bmorvai           #+#    #+#             */
/*   Updated: 2026/03/12 15:41:38 by bmorvai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static char	*ft_findstart(char const *s, char c)
{
	int		i;
	char	*ts;
	char	*start;

	i = 0;
	ts = (char *)s;
	while (ts[i])
	{
		if (ts[i] != c)
		{
			start = ts + i;
			return (start);
		}
		i++;
	}
	return (NULL);
}

static int	ft_count_words(char const *s, char c)
{
	int		count;
	int		i;
	char	*ts;

	ts = (char *)s;
	count = 0;
	i = 0;
	while (ts[i])
	{
		while (ts[i] == c)
			i++;
		if (ts[i] != '\0')
			count++;
		while (ts[i] && ts[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_findend(char const *s, char c)
{
	int		i;
	char	*ts;
	char	*end;

	i = 0;
	ts = (char *)s;
	while (ts[i])
	{
		if (ts[i] == c)
		{
			end = ts + i - 1;
			return (end);
		}
		else
		{
			i++;
		}
	}
	return (ts + i - 1);
}

char	*ft_wordcopy(char *start, char *end)
{
	char	*word;
	int		len;
	int		i;

	len = end - start + 1;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	*start;
	char	*end;
	int		i;
	char	**ptr;

	start = ft_findstart(s, c);
	i = 0;
	ptr = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (start)
	{
		end = ft_findend(start, c);
		ptr[i] = ft_wordcopy(start, end);
		if (!ptr[i])
		{
			i = 0;
			while (ptr[i])
				free(ptr[i++]);
			return (free(ptr), NULL);
		}
		i++;
		start = ft_findstart(end + 1, c);
	}
	return (ptr);
}
