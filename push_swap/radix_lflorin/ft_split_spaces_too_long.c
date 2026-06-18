/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces_too_long.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorin <lflorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:52:26 by lea               #+#    #+#             */
/*   Updated: 2026/05/29 13:29:39 by lflorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (count);
}

static int	next_word_start(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

static int	next_word_end(char *str, int i)
{
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

static char	**fill_split(char **result, char *str)
{
	int	i;
	int	count;
	int	start;
	int	end;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = next_word_start(str, i);
		if (!str[i])
			break ;
		start = i;
		end = next_word_end(str, i);
		result[count] = ft_substr(str, start, end - start);
		count++;
		i = end;
	}
	result[count] = NULL;
	return (result);
}

char	**ft_split_spaces(char *str)
{
	char	**result;
	int		count;

	if (!str)
		return (NULL);
	if (str[0] == '\0')
		return (error(), NULL);
	count = count_words(str);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	return (fill_split(result, str));
}
