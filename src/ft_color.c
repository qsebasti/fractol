/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:47:44 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/25 21:37:42 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_pal	init_pal(t_env *e)
{
	t_pal	pal[17];

	pal[0] = (t_pal){3, {FRA4, FRA2, FRA3}};
	pal[1] = (t_pal){4, {SUNSET4, SUNSET3, SUNSET2, SUNSET1}};
	pal[2] = (t_pal){4, {FLAMES4, FLAMES3, FLAMES2, FLAMES1}};
	pal[3] = (t_pal){4, {LIGHT4, LIGHT3, LIGHT2, LIGHT1}};
	pal[4] = (t_pal){4, {RED4, RED3, RED2, RED1}};
	pal[5] = (t_pal){5, {KID5, KID4, KID3, KID2, KID1}};
	pal[6] = (t_pal){5, {SUN5, SUN4, SUN3, SUN2, SUN1}};
	pal[7] = (t_pal){2, {0x383c3c, 0x00ff00}};
	pal[8] = (t_pal){2, {0x383c3c, 0x0000ff}};
	pal[9] = (t_pal){2, {0x383c3c, 0xff0000}};
	pal[10] = (t_pal){7, {AEC7, AEC6, AEC5, AEC4, AEC3, AEC2, AEC1}};
	pal[11] = (t_pal){5, {SWAN5, SWAN4, SWAN3, SWAN2, SWAN1}};
	pal[12] = (t_pal){5, {SWAN1, SWAN2, SWAN3, SWAN4, SWAN5}};
	pal[13] = (t_pal){5, {MUNCH5, MUNCH4, MUNCH3, MUNCH2, MUNCH1}};
	pal[14] = (t_pal){5, {BGT5, BGT4, BGT3, BGT2, BGT1}};
	pal[15] = (t_pal){5, {PURPLE5, PURPLE4, PURPLE3, PURPLE2, PURPLE1}};
	pal[16] = (t_pal){2, {0x000000, 0xffffff}};
	return (pal[e->palette]);
}

static int		fill_tab(t_env *e, int i, t_pal pal)
{
	int		j;
	t_col	col1;
	t_col	col2;
	t_col	toto;
	double	coef;

	j = -1;
	col1.color = pal.tab[(int)(i / (double)e->it_max * (pal.len - 1))];
	col2.color = pal.tab[(int)(i / (double)e->it_max * (pal.len - 1)) + 1];
	coef = i / (double)e->it_max * (pal.len - 1) -\
		(int)(i / (double)e->it_max * (pal.len - 1));
	while (++j < 4)
		toto.argb[j] = col1.argb[j] + (col2.argb[j] - col1.argb[j]) * coef;
	return (toto.color);
}

/*
**		Fonction de remplissage du tableau de couleurs en fonction de la
**		palette et du nombre d'iterations.
*/

int				*update_tab(t_env *e)
{
	t_pal	tmp;
	int		i;

	tmp = init_pal(e);
	i = -1;
	while (++i < e->it_max)
		e->colors[i] = fill_tab(e, i, tmp);
	return (e->colors);
}

int				*color_tab(t_env *e)
{
	t_pal	tmp;
	int		i;

	free(e->colors);
	if (!(e->colors = (int *)malloc(sizeof(int) * e->it_max)))
		fractol_error(3);
	tmp = init_pal(e);
	i = -1;
	while (++i < e->it_max)
		e->colors[i] = fill_tab(e, i, tmp);
	return (e->colors);
}

/*
**		Fonction pour dessiner la mosaique.
*/

int				color_m(t_env *e, int k, double tab[12])
{
	int		i;
	t_col	toto;
	t_col	col1;
	t_col	col2;
	t_pal	pal;

	pal = init_pal(e);
	col1.color = pal.tab[(int)(k / (double)e->it_max * (pal.len - 1))];
	col2.color = pal.tab[(int)(k / (double)e->it_max * (pal.len - 1)) + 1];
	i = -1;
	while (++i < 4)
		toto.argb[i] = col1.argb[i] + (col2.argb[i] - col1.argb[i]) *\
			(k - 1 + log(log(tab[ZR] + tab[ZI])) / log(2));
	return (toto.color);
}
