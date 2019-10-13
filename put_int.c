/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:32 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 19:35:11 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_int(char *str, t_flags print)
{
	print.width = (print.minus ? print.width : print.width - ft_strlen(str));
	if (print.space && *str != '-' && !print.plus)
	{
		write(1, " ", 1);
		g_count++;
	}
	print.width = ((print.plus || print.space) && print.flag != 'H' ? print.width - 1 : print.width);
	if (*str == '-')
	{
		write(1, "-", 1);
		str++;
		g_count++;
	}
	else if (print.plus)
	{
		write(1, "+", 1);
	}
	if (print.minus)
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
			print.width--;
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
		while (print.width > 0)
		{
			if (print.zero)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			print.width--;
			g_count++;
		}
		while (*str)
		{
			write(1, str, 1);
			str++;
			g_count++;
		}
	}
}
