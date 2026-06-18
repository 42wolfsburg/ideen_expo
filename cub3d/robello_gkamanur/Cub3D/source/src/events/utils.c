/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:18:28 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 20:36:15 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_controls(void)
{
	printf("\n");
	printf("╔════════════════════════════════════╗\n");
	printf("║         CUB3D CONTROLS             ║\n");
	printf("╠════════════════════════════════════╣\n");
	printf("║  ESC         - Exit program        ║\n");
	printf("║  W           - Move forward        ║\n");
	printf("║  S           - Move backward       ║\n");
	printf("║  A           - Strafe left         ║\n");
	printf("║  D           - Strafe right        ║\n");
	printf("║  ← / →       - Rotate view         ║\n");
	printf("║  Red X       - Close window        ║\n");
	printf("╚════════════════════════════════════╝\n");
	printf("\n");
}

void	error_exit(char *message)
{
	printf("Error: %s\n", message);
	exit(1);
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}
