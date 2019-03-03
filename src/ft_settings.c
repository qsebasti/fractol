/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:35:12 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/24 16:39:10 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_setenv(t_env *e)
{
	e->w = 0;
	e->h = 0;
	e->mouse_x = 0;
	e->mouse_y = 0;
	e->tab[0] = "Mandelbrot";
	e->tab[1] = "Julia";
	e->tab[2] = "Burningship";
	e->tab[3] = "Tricorn";
	e->tab[4] = "Celtic";
	e->tab[5] = "Wrong fractal";
	e->tab[6] = NULL;
	e->power = 1;
	e->it_max = 150;
	if (!(e->colors = (int *)malloc(sizeof(int))))
		fractol_error(3);
	e->colors = color_tab(e);
}

static void	get_help(char **info)
{
	info[0] = "CONTROLS";
	info[1] = "HIDE HELP   | H";
	info[2] = "ZOOM IN/OUT | SCROLL";
	info[3] = "ZOOM IN/OUT | L/R CLICK";
	info[4] = "JULIA MOVES | MOUSE";
	info[5] = "PAUSE       | SPC";
	info[6] = "MOVE        | ARROWS";
	info[7] = "ITER        | [+]/[-]";
	info[8] = "HEADS       | [*]/[/]";
	info[9] = "SWITCH FRACT| ENTER";
	info[10] = "SWITCH COLOR|SHIFT";
	info[11] = "MOSAIC      | M";
	info[12] = "AUTO COLOR  | A";
	info[13] = "RESET       | BCKSPC";
	info[14] = "BLUR        | F";
	info[15] = "QUIT        | ESC";
	info[16] = NULL;
}

static void	print_info_mlx(t_env *e)
{
	char	*info[17];
	int		i;
	char	**s;

	if (e->nb == JULIA)
		mlx_string_put(e->mlx, e->win, WIDTH / 2 - 20, 5, SNOW, e->tab[e->nb]);
	else
		mlx_string_put(e->mlx, e->win, WIDTH / 2 - 35, 5, SNOW, e->tab[e->nb]);
	if (!(s = (char **)malloc(sizeof(char *) * 5)))
		fractol_error(3);
	get_help(info);
	mlx_string_put(e->mlx, e->win, 5, 5, SNOW, s[0] = ft_itoa(e->mouse_x));
	mlx_string_put(e->mlx, e->win, 5, 20, SNOW, s[1] = ft_itoa(e->mouse_y));
	mlx_string_put(e->mlx, e->win, 5, 35, SNOW, s[2] = ft_strjoin("nb. iter: ",\
				s[3] = ft_itoa(e->it_max)));
	s[4] = NULL;
	ft_freesplit(s);
	i = -1;
	if (e->key[KEY_H])
		while (info[++i])
			mlx_string_put(e->mlx, e->win, 5, 55 + i * 22, SNOW, info[i]);
	else
		mlx_string_put(e->mlx, e->win, 5, 55, SNOW, "SHOW HELP | H");
}

void		print_string_mlx(t_env *e)
{
	if (e->key[KEY_C])
	{
		mlx_string_put(e->mlx, e->win, WIDTH / 2 - 50, 5, SNOW, e->tab[WRONG]);
		mlx_string_put(e->mlx, e->win, WIDTH / 2 - 40, HEIGHT / 2 - 50,\
				SNOW, "SIGNAL LOST");
	}
	else
		print_info_mlx(e);
}
