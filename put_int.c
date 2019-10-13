/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:32 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 22:10:36 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_int(char *str, t_flags print)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(str);
	print.width = (print.minus ? print.width : print.width - len);
	if (print.space && str[i] != '-' && !print.plus)
	{
		write(1, " ", 1);
		g_count++;
	}
	print.width = ((print.plus || print.space) && print.flag != 'H' ? print.width - 1 : print.width);
	if (str[i] == '-' && print.minus)
	{
		write(1, "-", 1);
		i++;
		g_count++;
	}
	if (print.plus && str[i] != '-' && print.precision <= 0)
	{
		write(1, "+", 1);
		g_count++;
	}
	if (print.minus)
	{
		while (i < len)
		{
			write(1, &str[i], 1);
			i++;
			print.width--;
			g_count++;
		}
		while (print.width > 0)
		{
			write(1, " ", 1);
			print.width--;
			g_count++;
			print.precision--;	
		}
		while (print.precision > 0)
		{
			write(1, "0", 1);
			g_count++;
		}
	}
	else
	{
		print.precision = print.precision - len;
		if (str[i] == '-')
		{
			write(1, "-", 1);
			i++;
			g_count++;
		}
		while (print.width > 0 || print.precision > 0)
		{
			if (print.zero || print.precision > 0)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			print.width--;
			g_count++;
			print.precision--;
		}
		while (i < len)
		{
			write(1, &str[i], 1);
			i++;
			g_count++;
		}
	}
}
