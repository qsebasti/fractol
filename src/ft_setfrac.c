/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setfrac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 14:24:02 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/24 20:23:51 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		set_mandelbrot(t_env *e)
{
	e->x1 = -2.2 * ((double)WIDTH / (double)HEIGHT);
	e->x2 = 0.8 * ((double)WIDTH / (double)HEIGHT);
	e->y1 = -1.5;
	e->y2 = 1.5;
	e->it_max = 150;
	e->stepx = (e->x2 - e->x1) / (double)WIDTH;
	e->stepy = (e->y2 - e->y1) / (double)HEIGHT;
}

static void		set_julia(t_env *e)
{
	e->x1 = -1.4 * ((double)WIDTH / (double)HEIGHT);
	e->x2 = 1.4 * ((double)WIDTH / (double)HEIGHT);
	e->y1 = -1.5;
	e->y2 = 1.5;
	e->it_max = 150;
	e->c_r = 0.285;
	e->c_i = 0.01;
	e->tmpx = e->x1;
	e->tmpy = e->y1;
	e->stepx = (e->x2 - e->x1) / (double)WIDTH;
	e->stepy = (e->y2 - e->y1) / (double)HEIGHT;
}

static void		set_tricorn(t_env *e)
{
	e->x1 = -2 * ((double)WIDTH / (double)HEIGHT);
	e->x2 = 1 * ((double)WIDTH / (double)HEIGHT);
	e->y1 = -1.8;
	e->y2 = 1.8;
	e->it_max = 150;
	e->stepx = (e->x2 - e->x1) / (double)WIDTH;
	e->stepy = (e->y2 - e->y1) / (double)HEIGHT;
}

static void		set_burning(t_env *e)
{
	e->x1 = -2 * ((double)WIDTH / (double)HEIGHT);
	e->x2 = 0.8 * ((double)WIDTH / (double)HEIGHT);
	e->y1 = -1.5;
	e->y2 = 1.0;
	e->it_max = 150;
	e->stepx = (e->x2 - e->x1) / (double)WIDTH;
	e->stepy = (e->y2 - e->y1) / (double)HEIGHT;
}

void			ft_set_frac(int i, t_env *e)
{
	if (i == MANDELBROT)
		set_mandelbrot(e);
	if (i == JULIA)
		set_julia(e);
	if (i == BURNING)
		set_burning(e);
	if (i == TRICORN)
		set_tricorn(e);
	if (i == CELTIC)
		set_mandelbrot(e);
}
