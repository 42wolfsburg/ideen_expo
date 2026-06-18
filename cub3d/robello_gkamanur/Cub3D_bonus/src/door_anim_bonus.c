/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:16:29 by robello           #+#    #+#             */
/*   Updated: 2026/01/23 19:17:32 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	update_door_animation(t_door *door, double delta_time)
{
	if (door->state == OPENING)
	{
		door->door_progress += DOOR_OPEN_SPEED * delta_time;
		if (door->door_progress >= DOOR_MAX_OPEN)
		{
			door->door_progress = DOOR_MAX_OPEN;
			door->state = OPEN;
		}
	}
	else if (door->state == CLOSING)
	{
		door->door_progress -= DOOR_SPEED * delta_time;
		if (door->door_progress <= 0.0)
		{
			door->door_progress = 0.0;
			door->state = CLOSED;
		}
	}
}

void	check_door_auto_close(t_door *door, double curr_time)
{
	if (door->state != OPEN)
		return ;
	if (door->last_opened == 0.0)
		door->last_opened = curr_time;
	else if (curr_time - door->last_opened > DOOR_AUTO_CLOSE / 1000.0)
		door->state = CLOSING;
}

void	check_secret_door_revel(t_game *game, t_door *door)
{
	if (door->is_secret == SECRET_DOOR_YES && door->revealed == 0)
	{
		if (game->colls.collected >= game->colls.total)
		{
			door->revealed = 1;
			printf("\n🎉 Secret door Revealed! 🎉\n");
		}
	}
}

void	update_doors(t_game *game, double delta_time)
{
	int		i;
	double	current_time;

	if (game->doors.count == 0)
		return ;
	game->game_time += delta_time;
	current_time = game->game_time;
	i = 0;
	while (i < game->doors.count)
	{
		check_secret_door_revel(game, &game->doors.list[i]);
		if (game->doors.list[i].is_secret == SECRET_DOOR_NO
			|| game->doors.list[i].revealed == 1)
		{
			update_door_animation(&game->doors.list[i], delta_time);
			check_door_auto_close(&game->doors.list[i], current_time);
		}
		i++;
	}
}

void	interact_with_door(t_game *game, int idx)
{
	t_door	*door;

	if (idx < 0 || idx >= game->doors.count)
		return ;
	door = &game->doors.list[idx];
	if (door->is_secret == SECRET_DOOR_YES && door->revealed == 0)
		return ;
	if (!is_player_near_door(game, door))
		return ;
	if (door->state == CLOSED)
	{
		door->state = OPENING;
		door->last_opened = game->game_time;
	}
	else if (door->state == OPEN || door->state == OPENING)
	{
		door->state = CLOSING;
		door->last_opened = 0.0;
	}
}
