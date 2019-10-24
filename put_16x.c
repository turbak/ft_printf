/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_16x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:39:31 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/24 16:03:04 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_16x(char *str, t_flags print)
{
	int len;
	int i;

	i = 0;
	g_count += (print.hash ? 2 : 0);
	len = ft_strlen(str) + (print.hash ? 2 : 0);
	if (print.precision || print.dot || print.minus)
		print.zero = '\0';
	print.width -= (print.precision > len ? print.precision + (print.hash ? 2 : 0) : len);
	print.precision -= len - (str[i] == '-' ? 1 : 0) - (print.hash ? 2 : 0);
	if (print.minus)
	{
		write(1, (print.hash == 'A' ? "0x" : "0X"), print.hash ? 2 : 0);
		while (print.precision > 0)
		{
			write(1, "0", 1);
			print.precision--;
			g_count++;
		}
		while (str[i])
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
		if ((print.precision > 0 || print.width > 0) && print.zero && print.hash)
			write(1, (print.hash ? "0x" : "0X"), 2);
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
		if (!print.zero && print.hash)
			write(1, (print.hash == 'A' ? "0x" : "0X"), 2);
		while (print.precision > 0)
		{
			write(1, "0", 1);
			print.precision--;
			g_count++;
		}
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
			g_count++;
		}
	}
	if (!(*str == '0' && !str[1]) && *str)
		free(str);
}
