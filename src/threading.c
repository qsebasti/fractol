/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 12:08:18 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/24 20:22:45 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		calcul2(t_env *e, double tab[12])
{
	int		i;
	double	tmpr;
	double	tmpi;

	i = -1;
	tmpr = tab[ZR];
	tmpi = tab[ZI];
	while (++i < e->power)
	{
		tab[TMP] = tab[ZR];
		if (e->nb == CELTIC)
			tab[ZR] = fabs(tmpr * tab[ZR] - tmpi * tab[ZI]);
		else
			tab[ZR] = tmpr * tab[ZR] - tmpi * tab[ZI];
		if (e->nb == BURNING)
			tab[ZI] = fabs(tab[ZI] * tmpr + tmpi * tab[TMP]);
		else
			tab[ZI] = tab[ZI] * tmpr + tmpi * tab[TMP];
	}
	tab[ZR] += tab[CR];
	tab[ZI] = (e->nb == TRICORN || e->nb == CELTIC ? -1 : 1) *\
			(tab[ZI] + tab[CI]);
}

static void		calcul(t_env *e, double tab[12], int *toto)
{
	while (tab[ZR] * tab[ZR] + tab[ZI] * tab[ZI] < 100 && ++tab[I] < e->it_max)
	{
		calcul2(e, tab);
	}
	tab[YMIN] += e->stepy;
	if (tab[I] != e->it_max)
		e->key[KEY_M] ? put_point(e, tab[X], tab[Y], color_m(e, tab[I], tab)) :\
			put_point(e, tab[X], tab[Y], toto[(int)tab[I]]);
	else
		put_point(e, tab[X], tab[Y], 0x000000);
}

static void		set_calc(t_env *e, int thread, double tab[12])
{
	while (++tab[X] < WIDTH / THREADS * (thread + 1))
	{
		tab[Y] = -1;
		tab[YMIN] = e->y1;
		while (++tab[Y] < HEIGHT)
		{
			if (e->nb == JULIA)
			{
				tab[ZR] = tab[XMIN];
				tab[ZI] = tab[YMIN];
				tab[CR] = e->c_r;
				tab[CI] = e->c_i;
			}
			else
			{
				tab[ZR] = 0;
				tab[ZI] = 0;
				tab[CR] = tab[XMIN];
				tab[CI] = tab[YMIN];
			}
			tab[I] = -1;
			calcul(e, tab, e->colors);
		}
		tab[XMIN] += e->stepx;
	}
}

static void		*routine(void *arg)
{
	t_th	*th;
	double	tab[12];

	th = (t_th *)arg;
	tab[XMIN] = th->env->x1 + ((th->env->x2 - th->env->x1) /\
			(double)THREADS * th->nb);
	tab[X] = WIDTH / THREADS * th->nb - 1;
	set_calc(th->env, th->nb, tab);
	pthread_exit(NULL);
}

void			threading(t_env *e)
{
	int			i;
	pthread_t	thread[THREADS];
	t_th		th[THREADS];

	i = 0;
	while (i < THREADS)
	{
		th[i].env = e;
		th[i].nb = i;
		pthread_create(&thread[i], NULL, routine, &th[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(thread[i++], NULL);
	if (e->key[KEY_F] || e->key[KEY_C])
		blur(e);
}
