/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:30:30 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/17 19:36:10 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_env *e)
{
	e->x1 = e->tx - (e->tx - e->x1) * 0.8;
	e->x2 = e->tx + (e->x2 - e->tx) * 0.8;
	e->y1 = e->ty - (e->ty - e->y1) * 0.8;
	e->y2 = e->ty + (e->y2 - e->ty) * 0.8;
}

void	zoom_out(t_env *e)
{
	e->x1 = e->tx - (e->tx - e->x1) / 0.8;
	e->x2 = e->tx + (e->x2 - e->tx) / 0.8;
	e->y1 = e->ty - (e->ty - e->y1) / 0.8;
	e->y2 = e->ty + (e->y2 - e->ty) / 0.8;
}
