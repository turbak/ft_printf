/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:06:23 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/27 20:59:08 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

long double	round_of(double nb, int power)
{
	while (power > 0)
	{
		nb *= 0.1;
		power--;
	}
	return (nb);
}

static char  *handle_dot(long double nb, t_flags print)
{
	int i;
	char *full;
	int	tmp;

	full = ft_strnew(print.precision + 1);
	full[0] = '.';
	tmp = 0;
	i = 1;
	while (i - 1 < print.precision)
	{
		if ((int)nb == 0)
			full[i] = '0';
		nb = (nb - tmp) * 10;
		tmp = (uintmax_t)nb;
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
	long double	round;

	print->precision = (!print->precision && !print->dot ? 6 : print->precision);
	round = round_of(0.5, print->precision);
	i = (n < 0 ? 1 : 0);
	dot[0] = (i == 1 ? '-' : '\0');
	n = (n < 0 ? -n : n);
	n += round;
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
	full = handle_dot(n, *print);
	dot[1] = (dot[0] == '-' && !dot[1] ? '0' : dot[1]);
	all = ft_strjoin((!*dot ? "0" : dot), (print->precision == -1 && !print->hash ? "" : full));
	print->precision = 0;
	return (all);
}
