/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:32 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/16 19:02:07 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_abs(int a)
{
	return (a >= 0 ? a : -a);
}

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
	if (print.plus)
		print.space = '\0';
	print.width -= (print.precision ? print.precision : len);
	print.precision -= len - (str[i] == '-' ? 1 : 0);
	if (print.space && str[i] != '-' && !print.plus)
	{
		write(1, " ", 1);
		g_count++;
		print.width--;
	}
	if (print.minus)
	{
		if (str[i] == '-')
		
		{
			write(1, "-", 1);
			i++;
			g_count++;
			print.plus = '\0';
		}
		if (print.plus && str[i] != '-' && print.precision >= 0)
		{
			write(1, "+", 1);
			g_count++;
			print.width--;
		}
		while (print.precision > 0)
		{
			write(1, "0", 1);
			print.precision--;
			g_count++;
		}
		while (i < len)
		{
			write(1, &str[i], 1);
			i++;
			g_count++;
		}
		while (print.width > 0)
		{
			write(1, " ", 1);
			print.width--;
			g_count++;
		}
	}
	else
	{
		if ((print.plus && print.zero && str[i] != '-') || ((print.plus || str[i] == '-') && print.precision >= 0 && print.width >= 0))
			print.width--;
		if ((str[i] == '-' || print.plus) && (print.width <= 0 || print.zero))
		{
			print.width -= (print.zero ? 0 : 1);
			print.plus = '\0';
			write(1, (str[i] == '-' ? "-" : "+"), 1);
			i += (str[i] == '-' ? 1 : 0);
			g_count++;

		}
		if ((print.plus || str[i] == '-') && (print.precision <= 0 && print.width <= 0))
		{
			write(1, (str[i] == '-' ? "-" : "+"), 1);
			i += (str[i] == '-' ? 1 : 0);
			g_count++;
			print.plus = '\0';

		}
		while ((print.width > 0 || print.precision > 0) && print.zero)
		{
			write(1, "0", 1);
			print.width--;
			g_count++;
			print.precision--;
		}
		while (print.width > 0 && !print.zero)
		{
			write(1, " ", 1);
			print.width--;
			g_count++;
		}
		if (print.plus || str[i] == '-')
		{
			write(1, (str[i] == '-' ? "-" : "+"), 1);
			g_count++;
			i += (str[i] == '-' ? 1 : 0);
		}
		while (print.precision > 0)
		{
			write(1, "0", 1);
			print.precision--;
			g_count++;
		}
		while (i < len)
		{
			write(1, &str[i], 1);
			i++;
			g_count++;
		}
	}
	if (*str)
		free(str);
}
