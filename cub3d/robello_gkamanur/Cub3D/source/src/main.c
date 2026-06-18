/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:26:48 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 20:26:42 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/rendering.h"

static int	setup_data(t_data *data, char *filename)
{
	printf("Starting Cub3D...\n");
	if (!parse_cub_file(filename, data))
	{
		free_data(data);
		return (0);
	}
	debug_print_config(data);
	return (1);
}

static int	initialize_graphics(t_data *data)
{
	if (init_window(data) != 0)
	{
		free_data(data);
		return (0);
	}
	if (!init_image(data))
	{
		cleanup_and_exit(data);
		return (0);
	}
	if (!load_textures(data))
	{
		cleanup_and_exit(data);
		return (0);
	}
	return (1);
}

static void	start_rendering(t_data *data)
{
	print_controls();
	printf("Rendering first frame...\n");
	render_frame(data);
	printf("✓ Initial render complete\n");
	setup_hooks(data);
	mlx_loop_hook(data->mlx_ptr, smooth_render_loop, data);
	printf("Entering main loop...\n");
	mlx_loop(data->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!handle_arguments(argc, argv))
		return (1);
	if (!setup_data(&data, argv[1]))
		return (1);
	if (!initialize_graphics(&data))
		return (1);
	start_rendering(&data);
	cleanup_and_exit(&data);
	return (0);
}
