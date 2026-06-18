/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:41:07 by triedel           #+#    #+#             */
/*   Updated: 2024/01/18 14:06:43 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include "display.h"

void	errexit(const char *msg)
{
	if (msg)
		ft_printf("Error: %s\n", msg);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_disp	disp;
	bool	multi;
	bool	loadres;

	multi = false;
	if (argc >= 3 && ft_strcmp(argv[1], "m") == 0)
		multi = true;
	else if (argc != 2)
		errexit("Invalid args");
	if (!disp_init(&disp, 1500, 1500, "FDF"))
	{
		disp_destroy(&disp);
		errexit("Error initializing display");
	}
	if (multi)
		loadres = disp_load(&disp, argc - 2, (char **) &argv[2]);
	else
		loadres = disp_load(&disp, argc - 1, (char **) &argv[1]);
	if (ft_lstsize(disp.models) > 0 && loadres)
		mlx_loop(disp.mlx);
	ft_printf("Error\n");
	disp_destroy(&disp);
	return (0);
}
