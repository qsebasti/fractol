/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powern.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:18:35 by qsebasti          #+#    #+#             */
/*   Updated: 2018/02/16 15:28:13 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_powern(double nb, int n)
{
	double ret;

	ret = nb;
	if (n == 0)
		return (1);
	if (n < 0)
		return (0);
	if (n == 1)
		return (nb);
	while (n > 1)
	{
		ret *= nb;
		n--;
	}
	return (ret);
}
