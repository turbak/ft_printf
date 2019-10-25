/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:32 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/25 22:41:40 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_int(char *str, t_flags print)
{
	int len;
	int i;

	if (!print.precision && print.dot && !ft_strcmp("0", str))
	{
		free(str);
		str = "";
	}
	i = 0;
	len = ft_strlen(str);
	if (print.precision || print.minus)
		print.zero = '\0';
	print.width -= (print.precision > len ? print.precision : len);
	print.precision -= len - (str[i] == '-' ? 1 : 0);
	if (print.space && str[i] != '-' && !print.plus)
	{
		write(1, " ", 1);
		g_count++;
		print.width--;
	}
	(print.minus ? put_int_minus(str, print, len, i)
	: put_int_plus(str, print, len, i));
	if (*str)
		free(str);
}

void	put_int_minus(char *str, t_flags print, int len, int i)
{
	if (str[i] == '-')
	{
		write(1, "-", (g_count += 1));
		i++;
		len--;
	}
	if (print.plus && *str != '-' && print.precision >= 0)
	{
		write(1, "+", (g_count += 1));
		print.width--;
	}
	while (print.precision > 0)
	{
		write(1, "0", 1);
		print.precision--;
		g_count++;
	}
	write(1, &str[i], len);
	g_count += len;
	while (print.width > 0)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
}

void	put_int_plus(char *str, t_flags print, int len, int i)
{
	if ((print.plus && print.zero && str[i] != '-') ||
	((print.plus || str[i] == '-') && print.precision >= 0 && print.width >= 0))
		print.width--;
	len -= (*str == '-' ? 1 : 0);
	if ((str[i] == '-' || print.plus) && (print.width <= 0 || print.zero))
	{
		print.width -= (print.zero ? 0 : 1);
		print.plus = '\0';
		write(1, (str[i] == '-' ? "-" : "+"), 1);
		g_count++;
		i += (str[i] == '-' ? 1 : 0);
	}
	if ((print.plus || str[i] == '-') && (print.precision <= 0
	&& print.width <= 0))
	{
		write(1, (str[i] == '-' ? "-" : "+"), 1);
		g_count++;
		i += (str[i] == '-' ? 1 : 0);
		print.plus = '\0';
	}
	put_int_plus2(str, print, &i);
	write(1, &str[i], len);
	g_count += len;
}

void	put_int_plus2(char *str, t_flags print, int *i)
{
	while ((print.width > 0 || print.precision > 0) && print.zero)
	{
		write(1, "0", 1);
		g_count++;
		print.width--;
		print.precision--;
	}
	while (print.width > 0 && !print.zero)
	{
		write(1, " ", 1);
		print.width--;
		g_count++;
	}
	if (print.plus || str[*i] == '-')
	{
		write(1, (str[*i] == '-' ? "-" : "+"), 1);
		g_count++;
		*i += (str[*i] == '-' ? 1 : 0);
	}
	while (print.precision > 0)
	{
		write(1, "0", 1);
		g_count++;
		print.precision--;
	}
}
