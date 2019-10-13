/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:32 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 16:10:03 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_int(char *str, t_flags print)
{
	print.width = (print.flag == '-' ? print.width : print.width - ft_strlen(str));
	if (print.flag == ' ' && *str != '-')
		write(1, " ", 1);
	if (print.flag == '+')
		write(1, (*str == '-' ? "-" : "+"), 1);
	if (print.flag == '-')
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
			print.width--;
		}
		while (print.width > 0)
		{
			if (print.flag == '0')
				write(1, "0", 1);
			else
				write(1, " ", 1);
			print.width--;		
		}
	}
	else
	{
		while (print.width > 0)
		{
			if (print.flag == '0')
				write(1, "0", 1);
			else
				write(1, " ", 1);
			print.width--;		
		}
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
}
