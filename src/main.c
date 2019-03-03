/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:46:09 by qsebasti          #+#    #+#             */
/*   Updated: 2019/03/03 18:37:58 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_name(char *s, t_env *e)
{
	e->nb = -1;
	if (!(ft_strcmp(s, "mandelbrot")))
		e->nb = MANDELBROT;
	else if (!(ft_strcmp(s, "julia")))
		e->nb = JULIA;
	else if (!(ft_strcmp(s, "burningship")))
		e->nb = BURNING;
	else if (!(ft_strcmp(s, "tricorn")))
		e->nb = TRICORN;
	else if (!(ft_strcmp(s, "celtic")))
		e->nb = CELTIC;
	e->palette = 0;
	ft_set_frac(e->nb, e);
	return (e->nb);
}

static int	quit(void)
{
	exit(1);
	return (0);
}

int			main(int ac, char **av)
{
	t_env e;

	e.temps = time(NULL);
	ft_setenv(&e);
	if (ac != 2 || check_name(av[1], &e) == -1)
	{
		e.nb = WRONG;
		ft_set_frac(0, &e);
		e.key[KEY_C] = 1;
	}
	if (e.key[KEY_C])
		ft_putendl(USAGE" celtic");
	if (!(e.mlx = mlx_init()) ||
			!(e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "fractol")))
		return (fractol_error(2));
	mlx_centertop_window(e.win);
	mlx_hook(e.win, KPRESS, KPRESSMASK, &keypress, &e);
	mlx_hook(e.win, KRELEASE, KRELEASEMASK, &keyrelease, &e);
	mlx_hook(e.win, MOTION, POINTERMOTIONMASK, &mousemovehook, &e);
	mlx_hook(e.win, DESTROY, SNOTIFYMASK, &quit, &e);
	mlx_hook(e.win, BPRESS, BPRESSMASK, &mousepress, &e);
	mlx_hook(e.win, BRELEASE, BRELEASEMASK, &mouserelease, &e);
	mlx_loop_hook(e.mlx, hook, &e);
	mlx_loop(e.mlx);
	return (0);
}
