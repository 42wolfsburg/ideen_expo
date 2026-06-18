/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:56:37 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 23:07:45 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_strings(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	cleanup_on_error(char *clean, char *line, int is_first)
{
	if (clean)
		free(clean);
	if (is_first)
		free(line);
	return (0);
}

int	cleanup_and_return(char **padded, char **processed, int ret_val)
{
	free_strings(padded);
	free_strings(processed);
	return (ret_val);
}

int	cleanup_padded(char **padded)
{
	free_strings(padded);
	return (write(2, "Error: Failed to process spaces\n", 32), 0);
}

int	cleanup_both(char **padded, char **processed)
{
	free_strings(padded);
	free_strings(processed);
	return (0);
}
