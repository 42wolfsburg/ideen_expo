/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:53:27 by triedel           #+#    #+#             */
/*   Updated: 2024/08/07 18:39:58 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

bool	game_key_pressed(t_game *game, int kc)
{
	unsigned int	b;
	unsigned int	bt;

	b = kc / 8;
	bt = kc % 8;
	if (b >= INPUT_STATE_SIZE)
		return (false);
	return (get_bit(game->input_state[b], bt));
}

void	game_set_key(t_game *game, int kc, int state)
{
	unsigned int	b;
	unsigned int	bt;

	b = kc / 8;
	bt = kc % 8;
	if (b >= INPUT_STATE_SIZE)
		return ;
	set_bit(&game->input_state[b], bt, state);
}
