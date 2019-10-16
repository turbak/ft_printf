/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:48:14 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/16 19:04:55 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putstl(wchar_t *str, t_flags print)
{
	int len;
	int i;
	
	if (!print.dot && !print.precision)
		str[0] = '\0';
	len = (ft_strlenw(str) > (size_t)print.precision && print.precision ? print.precision : ft_strlenw(str));
	i = 0;
	print.width = (print.minus ? print.width : print.width - len);
	if (print.minus)
	{
		while (i < len)
		{
			ft_unicode((wchar_t)str[i]);
			i++;
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
		while (i < len)
		{
			ft_unicode((wchar_t)str[i]);
			i++;
			g_count++;
		}
	}
}

void	putst(char *str, t_flags print)
{
	int len;
	int i;

	if (!print.precision && print.dot)
		str = "";
	if (!str)
		str = "(null)";
	len = (ft_strlen(str) > (size_t)print.precision && print.precision ? print.precision : ft_strlen(str));
	i = 0;
	print.width = (print.minus ? print.width : print.width - len);
	if (print.minus)
	{
		while (i < len)
		{
			ft_unicode((wchar_t)str[i]);
			i++;
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
		while (i < len)
		{
			ft_unicode((wchar_t)str[i]);
			i++;
			g_count++;
		}
	}
}
