/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:24:41 by loandrad          #+#    #+#             */
/*   Updated: 2023/06/08 15:24:40 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	match(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		while (n--)
		{
			if (s1[i] != s2[i])
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

static void	get_set(t_fractol *f, char **av)
{
	if (match(av[1], "mandelbrot", ft_strlen("mandelbrot")) == 0)
		f->set = MANDELBROT;
	else if (match(av[1], "julia", ft_strlen("julia")) == 0)
		f->set = JULIA;
	else
		help_msg(f);
}

static void	julia_init(t_fractol *f, int ac, char **av)
{
	if (f->set != JULIA || ac == 2)
	{
		f->kr = -0.766667;
		f->ki = -0.090000;
		return ;
	}
	if (ac == 3)
		help_msg(f);
	if (find_char(av[2], '.') == 1)
		help_msg(f);
	if (find_char(av[3], '.') == 1)
		help_msg(f);
	f->kr = ft_atof(av[2]);
	f->ki = ft_atof(av[3]);
	if (f->kr > 2.0 || f->kr < -2.0)
		help_msg(f);
	if (f->ki >= 2.0 || f->ki <= -2.0)
		help_msg(f);
}

static void	handle_args(t_fractol *f, int ac, char **av)
{
	get_set(f, av);
	if (f->set != JULIA && ac > 3)
		help_msg(f);
	else if (f->set == JULIA && ac > 5)
		help_msg(f);
	julia_init(f, ac, av);
}

int	main(int ac, char **av)
{
	t_fractol	f;

	if (ac < 2)
	{
		help_msg(NULL);
		return (1);
	}
	clean_init(&f);
	handle_args(&f, ac, av);
	init(&f);
	render(&f);
	mlx_hook(f.win, EVENT_CLOSE_BTN, 0, quit, &f);
	mlx_key_hook(f.win, key_event, &f);
	mlx_mouse_hook(f.win, mouse_event, &f);
	mlx_loop(f.mlx);
}
