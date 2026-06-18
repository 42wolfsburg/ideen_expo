/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:17:54 by gkamanur          #+#    #+#             */
/*   Updated: 2026/01/21 19:26:44 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

int	handle_close(t_data *data)
{
	printf("Window close button clicked\n");
	destroy_window(data);
	exit(0);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, EVENT_KEY_PRESS, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, EVENT_DESTROY, 0, handle_close, data);
	printf("✓ Event hooks registered\n");
}
