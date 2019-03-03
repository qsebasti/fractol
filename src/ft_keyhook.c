/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:11:28 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/26 19:54:04 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			keypress(int keycode, t_env *e)
{
	if (keycode == KEY_SPC)
		e->key[KEY_SPC] = (e->key[KEY_SPC] == 1 ? 0 : 1);
	else if (keycode == KEY_H)
		e->key[KEY_H] = (e->key[KEY_H] == 1 ? 0 : 1);
	else if (keycode == KEY_F)
		e->key[KEY_F] = (e->key[KEY_F] == 1 ? 0 : 1);
	else if (keycode == KEY_M)
		e->key[KEY_M] = (e->key[KEY_M] == 1 ? 0 : 1);
	else if (keycode == KEY_A)
		e->key[KEY_A] = (e->key[KEY_A] == 1 ? 0 : 1);
	else if (keycode != KEY_C)
		e->key[keycode] = 1;
	return (0);
}

int			keyrelease(int keycode, t_env *e)
{
	if (keycode == KEY_SPC || keycode == KEY_H || keycode == KEY_ENTER ||
			keycode == KEY_C || keycode == KEY_F || keycode == LSHIFT ||
			keycode == RSHIFT || keycode == KEY_M || keycode == KEY_A)
		return (0);
	else
		e->key[keycode] = 0;
	return (0);
}

static void	keyhook3(t_env *e)
{
	time_t	tmp;

	tmp = time(NULL);
	if (e->key[KEY_BCKSPC])
	{
		ft_set_frac(e->nb, e);
		ft_setenv(e);
		e->key[KEY_BCKSPC] = 0;
	}
	if (e->key[KEY_A])
		if (tmp - e->temps >= 2)
		{
			e->temps = tmp;
			e->key[RSHIFT] = 1;
		}
	if (e->key[LSHIFT] || e->key[RSHIFT])
	{
		if (e->key[RSHIFT])
			e->palette = (e->palette == 16 ? 0 : e->palette + 1);
		if (e->key[LSHIFT])
			e->palette = (e->palette == 0 ? 16 : e->palette - 1);
		e->colors = update_tab(e);
		e->key[LSHIFT] = 0;
		e->key[RSHIFT] = 0;
	}
}

static void	keyhook2(t_env *e)
{
	if (e->key[KEY_UP] || e->key[KEY_DOWN])
	{
		e->h = (e->key[KEY_UP] ? -(e->y2 - e->y1) * 0.05 :
				(e->y2 - e->y1) * 0.05);
		e->y1 += e->h;
		e->y2 += e->h;
	}
	if (e->key[KEY_RIGHT] || e->key[KEY_LEFT])
	{
		e->w = (e->key[KEY_RIGHT] ? (e->x2 - e->x1) * 0.05 :
				-((e->x2 - e->x1) * 0.05));
		e->x1 += e->w;
		e->x2 += e->w;
	}
	if (e->key[KEY_MULT])
	{
		e->power++;
		e->key[KEY_MULT] = 0;
	}
	if (e->key[KEY_DIV] && e->power > 1)
	{
		e->power--;
		e->key[KEY_DIV] = 0;
	}
}

int			keyhook(t_env *e)
{
	if (e->key[KEY_ESC])
		exit(1);
	if (e->key[KEY_ENTER])
	{
		e->nb = (e->nb == 4 ? 0 : e->nb + 1);
		ft_set_frac(e->nb, e);
		e->power = 1;
		e->key[KEY_ENTER] = 0;
	}
	if (e->key[KEY_PLUS] || (e->key[KEY_MINUS] && e->it_max > 10))
	{
		if (e->key[KEY_MINUS] && e->it_max > 10)
			e->it_max -= 5;
		else
			e->it_max += 5;
		e->colors = color_tab(e);
	}
	keyhook2(e);
	keyhook3(e);
	return (0);
}
