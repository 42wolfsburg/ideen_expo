/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_speed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:04:00 by robello           #+#    #+#             */
/*   Updated: 2026/01/25 22:10:13 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	show_resolution_menu(t_game *game)
{
	printf("\n\n======= GRAPHICS RESOLUTION =======\n");
	printf("\n  This Screen is:  %d x %d\n\n", game->max_w, game->max_h);
	printf("   1  =  640  x 360     - Very Low\n");
	printf("   2  =  800  x 450     - Low\n");
	printf("   3  =  960  x 540     - Low+\n");
	printf("   4  =  1024 x 576     - Standard-\n");
	printf("   5  =  1152 x 648     - Standard\n");
	printf("   6  =  1280 x 720     - HD (Fast)\n");
	printf("   7  =  1366 x 768     - Common Laptop\n");
	printf("   8  =  1600 x 900     - HD+ (Recommended)\n");
	printf("   9  =  1920 x 1080    - Full HD\n");
	printf("   10 =  2560 x 1440    - 2K\n");
	printf("   11 =  3840 x 2160    - 4K ⚠️\n");
	printf("\n Choose (1-11, or Enter for option 8): ");
}

int	get_confirmation(void)
{
	char	user_answer;

	scanf(" %c", &user_answer);
	if (user_answer == 'y' || user_answer == 'Y')
		return (1);
	return (0);
}

void	set_high_medium_speeds(t_game *game)
{
	if (game->res_choice >= 10)
	{
		game->player.move_speed = 0.098;
		game->player.rota_speed = 0.093;
		game->enemy_anim_frames = 9;
		game->coll_anim_frames = 3;
		printf("  ✓ Set to HIGH speed (4K/2K)\n");
	}
	else if (game->res_choice == 9)
	{
		game->player.move_speed = 0.058;
		game->player.rota_speed = 0.054;
		game->enemy_anim_frames = 15;
		game->coll_anim_frames = 10;
		printf("  ✓ Using DEFAULT speed\n");
	}
	else if (game->res_choice >= 7)
	{
		game->player.move_speed = MOVE_SPEED;
		game->player.rota_speed = ROTA_SPEED;
		game->enemy_anim_frames = 20;
		game->coll_anim_frames = 15;
		printf("  ✓ Using MEDIUM+ speed\n");
	}
	game->doors.door_speed = DOOR_SPEED;
}

void	set_low_speeds(t_game *game)
{
	if (game->res_choice >= 5)
	{
		game->player.move_speed = 0.028;
		game->player.rota_speed = 0.028;
		game->enemy_anim_frames = 30;
		game->coll_anim_frames = 20;
		printf("  ✓ Set to MEDIUM speed\n");
	}
	else if (game->res_choice >= 3)
	{
		game->player.move_speed = 0.020;
		game->player.rota_speed = 0.020;
		game->enemy_anim_frames = 40;
		game->coll_anim_frames = 35;
		printf("  ✓ Set to LOW+ speed\n");
	}
	else
	{
		game->player.move_speed = 0.009;
		game->player.rota_speed = 0.01;
		game->enemy_anim_frames = 75;
		game->coll_anim_frames = 50;
		printf("  ✓ Set to VERY LOW speed\n");
	}
	game->doors.door_speed = DOOR_SPEED;
}

void	set_speeds_for_resolution(t_game *game)
{
	double	mult;
	int		i;

	printf("  ✓ Setting up speeds for choice:  %d\n", game->res_choice);
	if (game->res_choice >= 5)
		set_high_medium_speeds(game);
	else
		set_low_speeds(game);
	if (game->res_choice >= 10)
		mult = 4.0;
	else if (game->res_choice >= 7)
		mult = 1.1;
	else if (game->res_choice >= 5)
		mult = 0.9;
	else if (game->res_choice >= 3)
		mult = 0.5;
	else
		mult = 0.3;
	i = 0;
	while (i < game->enemies.ene_count)
		game->enemies.list[i++].ene_speed = ENEMY_SPEED * mult;
}
