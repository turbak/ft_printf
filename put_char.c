/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:41:26 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/15 22:23:18 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_char(unsigned int c, t_flags print)
{
	print.width--;
	if (print.minus)
	{
		ft_unicode(c);
		g_count++;
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
			write(1, " ", 1);
			print.width--;
			g_count++;
		}
		ft_unicode(c);
		g_count++;
	}
}
