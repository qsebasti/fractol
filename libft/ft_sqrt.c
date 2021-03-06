/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:59:22 by qsebasti          #+#    #+#             */
/*   Updated: 2017/11/21 15:45:22 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int i;

	i = 2;
	if (nb < 1)
		return (0);
	if (nb == 1)
		return (nb);
	else
	{
		while (i <= nb / i)
			i++;
		i--;
		if (i * i == nb)
			return (i);
	}
	return (0);
}
