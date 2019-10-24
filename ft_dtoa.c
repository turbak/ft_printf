/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:06:23 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/24 15:28:00 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static char  *handle_dot(long double nb, int precision)
{
	int i;
	char *full;
	int	tmp;

	full = ft_strnew(precision + 1);
	full[0] = '.';
	tmp = 0;
	i = 1;
	while (i - 1 < precision)
	{
		if ((int)nb == 0)
			full[i] = '0';
		nb = (nb - tmp) * 10;
		tmp = (int)(nb + ((int)nb != 9 ? 0.1 : 0));
		full[i] = tmp + '0';
		i++;
	}
	full[i] = '\0';
	return (full);
}

char *ft_dtoa(long double n, t_flags *print)
{
	char dot[20];
	char *full;
	char *all;
	size_t i;
	long double *nb;
	long double dig;

	i = (n < 0 ? 1 : 0);
	dot[0] = (i == 1 ? '-' : '\0');
	n = (n < 0 ? -n : n);
	nb = &n;
	dig = 1;
	while ((int)((*nb) /= 10) != 0)
		dig *= 10;
	(*nb) *= dig * 10;
	while ((int)(*nb) != 0)
	{
		dot[i] = (char)((*nb) / dig + '0');
		*nb -= (int)((*nb) / dig) * dig;
		dig /= 10;
		i++;
	}
	dot[i] = '\0';
	full = handle_dot(n, print->precision);
	print->precision = 0;
	print->width = 0;
	all = ft_strjoin(dot, full);
	return (all);
}