/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:58:24 by cauranus          #+#    #+#             */
/*   Updated: 2019/10/13 18:04:00 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags init_print()
{
	t_flags print;
	
	print.flag = '\0';
	print.hash = '\0';
	print.index = 0;
	print.minus = '\0';
	print.plus = '\0';
	print.precision = 0;
	print.size = '\0';
	print.space = '\0';
	print.type = '\0';
	print.width = 0;
	print.zero = 0;
	return (print);
}