/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mousehook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:57:03 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/24 20:23:21 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mousemovehook(int x, int y, t_env *e)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		e->mouse_x = x;
		e->mouse_y = y;
		if (e->nb == JULIA && !e->key[KEY_SPC])
		{
			e->c_r = x * (e->x2 - e->x1) / (double)WIDTH + e->x1;
			e->c_i = y * (e->y2 - e->y1) / (double)HEIGHT + e->y1;
		}
	}
	return (0);
}

int		mousescroll(int button, int x, int y, t_env *e)
{
	e->tx = x / (double)WIDTH * (e->x2 - e->x1) + e->x1;
	e->ty = y / (double)HEIGHT * (e->y2 - e->y1) + e->y1;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (button == FWDSCROLL)
			zoom_in(e);
		if (button == BWDSCROLL && e->x2 - e->x1 < 10)
			zoom_out(e);
	}
	e->stepx = (e->x2 - e->x1) / (double)WIDTH;
	e->stepy = (e->y2 - e->y1) / (double)HEIGHT;
	return (0);
}

int		mousepress(int button, int x, int y, t_env *e)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		e->mouse[button] = 1;
		mousescroll(button, x, y, e);
	}
	return (0);
}

int		mouserelease(int button, int x, int y, t_env *e)
{
	e->mouse[button] = 0;
	x = y;
	return (0);
}

int		mousehook(t_env *e)
{
	e->tx = e->mouse_x / (double)WIDTH * (e->x2 - e->x1) + e->x1;
	e->ty = e->mouse_y / (double)HEIGHT * (e->y2 - e->y1) + e->y1;
	if (e->mouse[LCLICK])
		zoom_in(e);
	if (e->mouse[RCLICK] && e->x2 - e->x1 < 10)
		zoom_out(e);
	e->stepx = (e->x2 - e->x1) / (double)WIDTH;
	e->stepy = (e->y2 - e->y1) / (double)HEIGHT;
	return (0);
}
