/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:53:27 by nradin            #+#    #+#             */
/*   Updated: 2023/03/03 13:17:16 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	init_comp(t_comp *comps)
{
	comps->exit = 0;
	comps->player = 0;
	comps->collect = 0;
}

void	throw_error(t_game *game, t_comp *comps, char *message)
{
	if (game)
		free_game(game);
	if (comps)
		free(comps);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

size_t	ft_strstr_len(char **str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

char	**ft_strstrdup(char **str, int size)
{
	char	**res;
	int		i;

	res = (char **)ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (i < size)
	{
		res[i] = ft_strdup(str[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_strstr_free(char **str)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strstr_len(str);
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
