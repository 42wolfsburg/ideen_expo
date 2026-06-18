/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:36:19 by loandrad          #+#    #+#             */
/*   Updated: 2023/06/08 15:35:09 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_up(int exit_code, t_fractol *f)
{
	if (!f)
		exit(exit_code);
	if (f->palette)
		free(f->palette);
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->win && f->mlx)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
	{
		free(f->mlx);
	}
	exit(exit_code);
}

int	quit(t_fractol *mlx)
{
	clean_up(0, mlx);
	return (0);
}

int	error(char *str1, int errno)
{
	write(2, "Fractol: ", 9);
	write(2, str1, ft_strlen(str1));
	write(2, "\n", 1);
	return (errno);
}

static void	program_options(void)
{
	write(1, "\n", 1);
	write(1, "RUN COMMANDS:\n", 14);
	write(1, "./fractol mandelbrot\n", 21);
	write(1, "or\n", 3);
	write(1, "./fractol julia\n", 16);
	write(1, "or\n", 3);
	write(1, "./fractol julia x.x x.x\n", 24);
	write(1, "\n", 1);
	write(1, "KEEP IN MIND:\n", 14);
	write(1, "Only lower case and replace x's with decimal numbers", 52);
	write(1, " between -2.0 and 2.0\n", 22);
	write(1, "\n", 1);
}

void	help_msg(t_fractol *f)
{
	program_options();
	clean_up(EXIT_FAILURE, f);
}
