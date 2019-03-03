/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 19:43:27 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/23 17:24:44 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	game_over(t_env *e)
{
	if (e->nb == WRONG)
	{
		if ((time(NULL) - e->temps) > 5)
			exit(1);
	}
}

static void	redraw(t_env *e)
{
	mlx_clear_window(e->mlx, e->win);
	if (!(e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT)))
		fractol_error(2);
	e->data = mlx_get_data_addr(e->img, &(e->bpp), &(e->s_len), &(e->end));
	game_over(e);
	threading(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_string_mlx(e);
	mlx_destroy_image(e->mlx, e->img);
}

int			hook(t_env *e)
{
	keyhook(e);
	mousehook(e);
	redraw(e);
	return (0);
}
