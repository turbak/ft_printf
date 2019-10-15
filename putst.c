/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:48:14 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/15 22:22:40 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putst(char *str, t_flags print)
{
	int len;
	int i;

	if (!str)
		str = "(null)";
	len = (ft_strlen(str) > (size_t)print.precision && print.precision ? print.precision : ft_strlen(str));
	i = 0;
	print.width = (print.minus ? print.width : print.width - len);
	if (print.minus)
	{
		while (i < len)
		{
			ft_unicode(str[i]);
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
			ft_unicode(str[i]);
			i++;
			g_count++;
		}
	}
}
