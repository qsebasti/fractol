/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:35:12 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/16 21:48:19 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			fractol_error(int a)
{
	if (a == 2)
		ft_putendl("mlx error");
	if (a == 3)
		ft_putendl("malloc error");
	exit(1);
	return (0);
}

static void	color(t_env *e, int div, char *data)
{
	t_col	color[4];
	t_col	ret;
	int		i;

	color[0].color = (e->x % WIDTH != WIDTH - 1 ? *((int *)&(data[(e->x + 1) *\
					e->bpp / 8 + e->y * e->s_len])) : 0);
	color[1].color = (e->x % WIDTH != 0 ? *((int *)&(data[(e->x - 1) * e->bpp /\
					8 + e->y * e->s_len])) : 0);
	color[2].color = (e->y % HEIGHT != HEIGHT - 1 ? *((int *)&(data[e->x *\
					e->bpp / 8 + (e->y + 1) * e->s_len])) : 0);
	color[3].color = (e->y % HEIGHT != 0 ? *((int *)&(data[e->x * e->bpp / 8 +\
					(e->y - 1) * e->s_len])) : 0);
	i = -1;
	while (++i < 4)
	{
		ret.argb[i] = (color[0].argb[i] + color[1].argb[i] +\
				color[2].argb[i] + color[3].argb[i]) / div;
	}
	put_point(e, e->x, e->y, ret.color);
}

void		blur(t_env *e)
{
	int		i;
	char	*data;

	if (!e->key[KEY_F] && !e->key[KEY_C])
		return ;
	if (!(data = malloc(1)))
		fractol_error(3);
	e->x = -1;
	while (++e->x < WIDTH)
	{
		e->y = -1;
		while (++e->y < HEIGHT)
		{
			i = 4;
			if (e->x % WIDTH == WIDTH - 1 || e->x % WIDTH == 0)
				i--;
			if (e->y % HEIGHT == HEIGHT - 1 || e->y % HEIGHT == 0)
				i--;
			e->key[KEY_C] == 1 ? color(e, i, data) : color(e, i, e->data);
		}
	}
	free(data);
}
